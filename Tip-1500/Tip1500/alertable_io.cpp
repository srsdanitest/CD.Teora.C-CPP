#include "CmnHdr.H"
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Resource.H"

//////////////////////////////////////////////////////////////////////
HANDLE CreateNewCompletionPort(DWORD cSimultaneousClients){
	return(CreateIoCompletionPort(INVALID_HANDLE_VALUE,
		NULL, 0, cSimultaneousClients));
}

BOOL AssociateDeviceWithCompletionPort(
	HANDLE hCompPort, HANDLE hDevice, DWORD dwCompKey){
	HANDLE h = CreateIoCompletionPort(hDevice,
		hCompPort, dwCompKey, 0);
	return(h == hCompPort);
}

//////////////////////////////////////////////////////////////////////

static BOOL PrepareDstFile(LPCTSTR pszFileSrc,
						   LPCTSTR pszFileDst,
						   PHANDLE phFileSrc, PHANDLE phFileDst,
						   PULARGE_INTEGER pulFileSize, DWORD dwPageSize) {

	ULARGE_INTEGER ulFileSizeDst;
	DWORD dwError;
	BOOL fOk = FALSE;

	_try{
		//Open the existing source file for input.
		*phFileSrc = CreateFile(pszFileSrc, GENERIC_READ,
			FILE_SHARE_READ, NULL, OPEN_EXISTING,
			FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
			NULL);

		if (*phFileSrc == INVALID_HANDLE_VALUE)
			_leave;

		//Create the new destination file for output.
		*phFileDst = CreateFile(pszFileDst, GENERIC_WRITE,
			0, NULL, CREATE_ALWAYS,
			FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
			*phFileSrc);
		if (*phFileDst == INVALID_HANDLE_VALUE)
			_leave;

		//Get the size of the original file.
		pulFileSize->LowPart = GetFileSize(*phFileSrc,
			&pulFileSize->HighPart);

		//Round up the sourc file size 
		//to an even multiple of pages.
		ulFileSizeDst.QuadPart = (pulFileSize->QuadPart + 
			dwPageSize - 1) & ~(dwPageSize - 1);

		//Force the destination file to the size needed.
		dwError = SetFilePointer(*phFileDst,
			ulFileSizeDst.LowPart,
			(PLONG)ulFileSizeDst.HighPart, FILE_BEGIN);
		if ((dwError == 0xffffffff) &&
			(GetLastError() != NO_ERROR))
			_leave;

		if (!SetEndOfFile(*phFileDst))
			_leave;

		fOk = TRUE;		//We did everything successfully.
	}
	_finally {
		//If anything failed, clean up entirely.
		if (!fOk) {
			if (*phFileSrc != INVALID_HANDLE_VALUE){
				CloseHandle(*phFileSrc);
				*phFileSrc = INVALID_HANDLE_VALUE;
			}
			if (*phFileSrc != INVALID_HANDLE_VALUE){
				CloseHandle(*phFileDst);
				*phFileDst = INVALID_HANDLE_VALUE;
			}
		}
	}
	return(fOk);
}

//////////////////////////////////////////////////////////////////////

static void CopyCleanup(LPCTSTR pszFileDst, HANDLE hFileSrc,
						HANDLE hFileDst, PULARGE_INTEGER pulFileSize){

	//Close the source and destination files.
	CloseHandle(hFileDst);
	CloseHandle(hFileSrc);
	
	//We need another handle to the destination file that is 
	//opened without FILE_FLAG_NO_BUFFERING. This allows us
	//to set the end-of-file marker to a position that is 
	//not sector-aligned.
	hFileDst = CreateFile(pszFileDst, GENERIC_WRITE,
	FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
	OPEN_EXISTING, 0, NULL);

	if (hFileDst != INVALID_HANDLE_VALUE){

		//Set the destination file's size to the size of the 
		//source file, in case the size of the source file was 
		//not a multiple of the page size.
		SetFilePointer(hFileDst, pulFileSize->LowPart, 
			(PLONG)pulFileSize->HighPart, FILE_BEGIN);
		SetEndOfFile(hFileDst);
		CloseHandle(hFileDst);
	}
}

//////////////////////////////////////////////////////////////////////
typedef struct {
	//The page soze used on the host machine
	DWORD dwPageSize;

	//Handles of the source and destination files
	HANDLE hFileSrc, hFileDst;

	//Size of source file
	ULARGE_INTEGER ulFileSize;

	//Offset in source file where next read begins
	ULARGE_INTEGER ulNextReadOffset;
	
	//The number of pending read and write I/O requests
	int nReadsInProgress;
	int nWritesInProgress;
} COPYSTATE, *PCOPYSTATE;

//Each IO requires an OVERLAPPED structure and a buffer.
typedef struct {
	OVERLAPPED Overlapped;
	PBYTE pbData;
} IOREQ, *PIOREQ;

#define MAX_PENDING_IO_REQS 4
#define BUFFSIZE			(64 * 1024)

//The keys indicating the type of completed IO
#define COMPKEY_READ 1
#define COMPKEY_WRITE 2

//////////////////////////////////////////////////////////////////////

BOOL FileCopy (LPCTSTR pszFileSrc, LPCTSTR pszFileDst){

	//We need a local copy state variable.
	COPYSTATE cs;

	//Maintain info about each IO request.
	IOREQ IOReq[MAX_PENDING_IO_REQS] = { 0 };

	SYSTEM_INFO si;
	int nIOReq;
	BOOL fOk, fDone = FALSE;

	// I/O Completion Port where read and writes complete to 
	HANDLE hIOCompPort = NULL;

	DWORD dwNumBytesXfer, dwCompKey;
	LPOVERLAPPED pOverlapped;

	// Initialize the global COPYSTATE variable.
	GetSystemInfo(&si);
	cs.dwPageSize = si.dwPageSize;
	cs.ulNextReadOffset.QuadPart = 0;
	cs.nReadsInProgress = 0;
	cs.nWritesInProgress = 0;

	//Open the existing source file for input.
	fOk = PrepareDstFile(pszFileSrc, pszFileDst,
		&cs.hFileSrc, &cs.hFileDst,
		&cs.ulFileSize, cs.dwPageSize);
	if (!fOk)
		return(fOk);

	//Create a new completion port kernel object.
	hIOCompPort = CreateNewCompletionPort(0);
	chASSERT(hIOCompPort != NULL);

	//Associate completed IOs to/from the source file with
	//IO Completion Port.  All completed IOs have a 
	// completion key of COMPKEY_READ.
	chVERIFY(AssociateDeviceWithCompletionPort(hIOCompPort, 
		cs.hFileDst, COMPKEY_READ));

	//Associate completed IOs to/from the destination file
	//with IO Completion Port.  All completed IOs have a 
	// completion key of COMPKEY_WRITE.
	chVERIFY(AssociateDeviceWithCompletionPort(hIOCompPort,
		cs.hFileDst, COMPKEY_WRITE));

	//Start the copy engine by posting a number of read 
	//IO requests against the source file.
	for (nIOReq = 0; nIOReq < MAX_PENDING_IO_REQS;
	nIOReq++) {
		IOReq[nIOReq].Overlapped.Internal = 0;
		IOReq[nIOReq].Overlapped.InternalHigh = 0;
		IOReq[nIOReq].Overlapped.Offset = 0;
		IOReq[nIOReq].Overlapped.OffsetHigh = 0;
		IOReq[nIOReq].Overlapped.hEvent = NULL;
		IOReq[nIOReq].pbData = VirtualAlloc(NULL,
			BUFFSIZE, MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE);

		cs.nWritesInProgress++;
		PostQueuedCompletionStatus(hIOCompPort, 0,
			COMPKEY_WRITE, &IOReq[nIOReq].Overlapped);
	}

	//Loop untill an error has occurred or until the 
	//destination file has been written.
	while ((cs.nReadsInProgress > 0) ||
		(cs.nWritesInProgress > 0)) {
		PIOREQ pIOReq;
		fOk = GetQueuedCompletionStatus(hIOCompPort,
			&dwNumBytesXfer, &dwCompKey, &pOverlapped,
			INFINITE);
		chASSERT(fOk || (GetLastError() == NO_ERROR));
		pIOReq = (PIOREQ) pOverlapped;

		switch (dwCompKey){
		case COMPKEY_READ:
			cs.nReadsInProgress--;
			//Round up the number of bytes to write
			//to a sector boundary.
			dwNumBytesXfer =
				(dwNumBytesXfer + cs.dwPageSize - 1) &
				~(cs.dwPageSize - 1);
			fOk = WriteFile(cs.hFileDst, pIOReq->pbData,
				dwNumBytesXfer, &dwNumBytesXfer,
				pOverlapped);
			// The write either completed or is pending.
			chASSERT(fOk || (!fOk &&
				(GetLastError() == ERROR_IO_PENDING)));
			cs.nWritesInProgress++;
			break;

		case COMPKEY_WRITE:
			cs.nWritesInProgress--;
			if (cs.ulNextReadOffset.QuadPart >=
				cs.ulFileSize.QuadPart)
				break;

			//We haven't read past the end of the file yet.
			//Read the next chunk of data.
			pOverlapped->Offset =
				cs.ulNextReadOffset.LowPart;
			pOverlapped->OffsetHigh =
				cs.ulNextReadOffset.HighPart;
			fOk = ReadFile(cs.hFileSrc, pIOReq->pbData,
				BUFFSIZE, &dwNumBytesXfer, pOverlapped);
			//The read either completed or is pending.
			chASSERT(fOk || (!fOk &&
				(GetLastError() == ERROR_IO_PENDING)));
			cs.nReadsInProgress++;
			//Offset in source file where next read begins
			cs.ulNextReadOffset.QuadPart += BUFFSIZE;
			break;
		}
	}

	//Destroy the I/O completion port.
	CloseHandle(hIOCompPort);

	//Free the memory buffers used for the copy.
	for (nIOReq = 0; nIOReq < MAX_PENDING_IO_REQS;
	nIOReq++){
		VirtualFree(IOReq[nIOReq].pbData, 0, MEM_RELEASE);
	}

	//Close the source and destination files; force the 
	//destination file to be the same size as the source.
	CopyCleanup(pszFileDst, cs.hFileSrc, cs.hFileDst,
		&cs.ulFileSize);

	return(TRUE);
	}

//////////////////////////////////////////////////////////////////////

BOOL Dlg_OnInitDialog (HWND hwnd, HWND hwndFocus,
					  LPARAM lParam){

	//Associate an icon with the dialog box.
	chSETDLGICONS(hwnd, IDI_IOCMPPRT, IDI_IOCMPPRT);

	//Disable the "Copy" button because no file 
	//has been selected yet.
	EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);

	return(TRUE);
}

//////////////////////////////////////////////////////////////////////

void Dlg_OnCommand(HWND hwnd, int id, 
				   HWND hwndCtl, UINT codeNoteify){

	TCHAR szPathname[_MAX_DIR];
	BOOL fOk;
	OPENFILENAME ofn;

	switch (id) {
	case IDOK:
		//Copy the source file to the destination file.
		Static_GetText(GetDlgItem(hwnd, IDC_SRCFILE),
			szPathname, sizeof(szPathname));
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		FileCopy(szPathname, _TEXT("IOCmpPrt.CPY"));
		break;

	case IDC_BROWSE:
		chINITSTRUCT(ofn, TRUE);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFilter = _TEXT("*.*\0");
		_tcscpy(szPathname, _TEXT("*.*"));
		ofn.lpstrFile = szPathname;
		ofn.nMaxFile = sizeof(szPathname);
		ofn.Flags = OFN_FILEMUSTEXIST;
		fOk = GetOpenFileName(&ofn);

		if (fOk) {
			HANDLE hFile;
			Static_SetText(GetDlgItem(hwnd, IDC_SRCFILE),
				szPathname);
			hFile = CreateFile(szPathname, GENERIC_READ,
				0, NULL, OPEN_EXISTING, 0, NULL);

			SetDlgItemInt(hwnd, IDC_SRCFILESIZE,
				GetFileSize(hFile, NULL), FALSE);
			CloseHandle(hFile);
		}

		//Enable the "Copy" button if the user selected 
		//a valid pathname.
		GetWindowText(GetDlgItem(hwnd, IDC_SRCFILE),
			szPathname, sizeof(szPathname));
		EnableWindow(GetDlgItem(hwnd, IDOK),
			szPathname[0] != _TEXT('('));
		if (fOk){
			// If the user pressed the OK button in the file 
			//dialog box, change focus to the "Copy" button
			FORWARD_WM_NEXTDLGCTL(hwnd, 
				GetDlgItem(hwnd, IDOK), TRUE, SendMessage);
		}
		break;

	case IDCANCEL:
			EndDialog(hwnd, id);
			break;
	}
}

//////////////////////////////////////////////////////////////////////

BOOL CALLBACK Dlg_Proc (HWND hwnd, UINT uMsg,
						WPARAM wParam, LPARAM lParam){

	switch (uMsg){
		chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
		chHANDLE_DLGMSG(hwnd, WM_COMMAND, Dlg_OnCommand);
	}
	
	return(FALSE);
}

//////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
 {

 	chWARNIFUNICODEUNDERWIN95();
 	DialogBox(hInstance, MAKEINTRESOURCE(IDD_IOCMPPRT), NULL, Dlg_Proc);

	return(0);
  }

//////////////////////////End Of File/////////////////////////////////









