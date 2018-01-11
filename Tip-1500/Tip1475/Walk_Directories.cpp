//
// Walk_Directories.cpp
//

#include "CmnHdr.H"
#include <windows.h>
#include <windowsx.h>

#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Resource.H"

static BOOL IsChildDir (WIN32_FIND_DATA *lpFindData) 
{
  return(
    ((lpFindData->dwFileAttributes &
      FILE_ATTRIBUTE_DIRECTORY) != 0) &&
      (lstrcmp(lpFindData->cFileName, _TEXT(".")) !=0) &&
      (lstrcmp(lpFindData->cFileName, _TEXT("..")) != 0));
}

static BOOL FindNextChildDir (HANDLE hFindFile, WIN32_FIND_DATA *lpFindData)
{
  BOOL fFound = FALSE;

  do
  {
    fFound = FindNextFile(hFindFile, lpFindData);
  } while (fFound && !IsChildDir(lpFindData));

  return(fFound);
}

static HANDLE FindFirstChildDir (LPTSTR szPath, WIN32_FIND_DATA *lpFindData)
{
  BOOL fFound;
  HANDLE hFindFile = FindFirstFile(szPath, lpFindData);

  if (hFindFile != INVALID_HANDLE_VALUE)
  {
    fFound = IsChildDir(lpFindData);

    if (!fFound)
      fFound = FindNextChildDir(hFindFile, lpFindData);

    if (!fFound)
    {
      FindClose(hFindFile);
      hFindFile = INVALID_HANDLE_VALUE;
    }
  }
  return (hFindFile);
}

// To minimize stack use, one instance of the DIRWALKDATA structure is
// created as a local variable in DirWalk.C, and a pointer to it is passed
// to DirWalkRecurse()

// Data Used by DirWalkRecurse
typedef struct
{
  HWND hwndTreeLB;          	// Handle to the output list box
  int nDepth;               	// Nesting depth
  BOOL fRecurse;            	// Set to TRUE to list subdirectories
  TCHAR szBuf[1000];        	// Output formatting buffer
  int nIndent;              	// Indentation character count
  BOOL fOk;                 	// Loop control flag
  BOOL fIsDir;               	// Loop control flag
  WIN32_FIND_DATA FindData;  	// File information
} DIRWALKDATA, *LPDIRWALKDATA;

// Walk the directory structure and fill a ListBox control with filenames.
// If pDW->fRecurse is set, list any child directories by recursively calling
// DirWalkRecurse.

static void DirWalkRecurse (LPDIRWALKDATA pDW)
{
  HANDLE hFind;

  pDW->nDepth++;

  pDW->nIndent = 3 * pDW->nDepth;
  _stprintf(pDW->szBuf, _TEXT("%*s"), pDW->nIndent, _TEXT(""));

  GetCurrentDirectory(chDIMOF(pDW->szBuf) - pDW->nIndent, &pDW->szBuf[pDW->nIndent]);
  ListBox_AddString(pDW->hwndTreeLB, pDW->szBuf);

  hFind = FindFirstFile(_TEXT("*.*"), &pDW->FindData);
  pDW->fOk = (hFind != INVALID_HANDLE_VALUE);

  while (pDW->fOk)
  {
    pDW->fIsDir = pDW->FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
    if (!pDW->fIsDir || (!pDW->fRecurse && IsChildDir(&pDW->FindData)))
    {
      _stprintf(pDW->szBuf,
        pDW->fIsDir ? _TEXT("%*s[%s]") : _TEXT("%*s%s"),
        pDW->nIndent, _TEXT(""),
        pDW->FindData.cFileName);

      ListBox_AddString(pDW->hwndTreeLB, pDW->szBuf);
    }
    pDW->fOk = FindNextFile(hFind, &pDW->FindData);
  }
  if (hFind != INVALID_HANDLE_VALUE)
    FindClose(hFind);

  if (pDW->fRecurse)
  {
    // Get the first child directory
    hFind = FindFirstChildDir(_TEXT("*.*"), &pDW->FindData);
    pDW->fOk = (hFind != INVALID_HANDLE_VALUE);
    while (pDW->fOk)
    {
      // Change into the child directory
      if (SetCurrentDirectory(pDW->FindData.cFileName))
      {
        // Perform the recursive walk into the child directory.
        // Remember that some members of pDW will be overwritten by this call.
        DirWalkRecurse(pDW);

        // Change back to the child's parent directory.
        SetCurrentDirectory(_TEXT(".."));
      }
      pDW->fOk = FindNextChildDir(hFind, &pDW->FindData);
    }
    if (hFind != INVALID_HANDLE_VALUE)
      FindClose(hFind);
  }
  pDW->nDepth--;
}

// Walk the directory structure and fill a ListBox with filenames.
// This function sets up a call to DirWalkRecurse, which does the real work.

void DirWalk (
              HWND hwndTreeLB,              // ListBox to fill
              LPCTSTR pszRootPath,          // Starting point of the tree walk
              BOOL fRecurse                 // Expand subdirectories
              )
{
  TCHAR szCurrDir[_MAX_DIR];
  DIRWALKDATA DW;                 // Create instance of DIRWALKDATA

  // Clear the ListBox
  ListBox_ResetContent(hwndTreeLB);

  // Save the current directory so that it can be restored later.
  GetCurrentDirectory(chDIMOF(szCurrDir), szCurrDir);

  // Set the current directory to where you want to start walking
  SetCurrentDirectory(pszRootPath);

  // nDepth is used to control indenting. The value -1 will cause
  // the first level to display flush left.
  DW.nDepth = -1;

  DW.hwndTreeLB = hwndTreeLB;
  DW.fRecurse = fRecurse;

  // Call the recursive function to walk the subdirectories.
  DirWalkRecurse(&DW);
 
  // Restore the current directory to what it was before the function was called.
  SetCurrentDirectory(szCurrDir);
}

BOOL Dlg_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
  RECT rc;

  // Associate an icon with the dialog box.
  chSETDLGICONS(hwnd, IDI_DIRWALK, IDI_DIRWALK);

  DirWalk(GetDlgItem(hwnd, IDC_TREE), _TEXT("\\"), TRUE);

  GetClientRect(hwnd, &rc);
  SetWindowPos(GetDlgItem(hwnd, IDC_TREE), NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER);

  return(TRUE);
}

void Dlg_OnSize (HWND hwnd, UINT state, int cx, int cy)
{
  SetWindowPos(GetDlgItem(hwnd, IDC_TREE), NULL, 0, 0, cx, cy, SWP_NOZORDER);
}

void Dlg_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT CodeNotify)
{
  switch (id)
  {
  case IDCANCEL:
    EndDialog(hwnd, id);
    break;

  case IDOK:
    // Call the recursive routine to walk the tree
    DirWalk(GetDlgItem(hwnd, IDC_TREE), _TEXT("\\"), TRUE);
    break;
  }
}

BOOL CALLBACK Dlg_Proc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
    chHANDLE_DLGMSG(hwnd, WM_SIZE, Dlg_OnSize);
    chHANDLE_DLGMSG(hwnd, WM_COMMAND, Dlg_OnCommand);
  }
  return(FALSE);
}

int WINAPI WinMain(HINSTANCE hinstExe, HINSTANCE hinstPrev, LPSTR pszCmdLine, int nCmdShow)
{
  chWARNIFUNICODEUNDERWIN95();
  DialogBox(hinstExe, MAKEINTRESOURCE(IDD_DIRWALK), NULL, Dlg_Proc);
  return(0);
}
