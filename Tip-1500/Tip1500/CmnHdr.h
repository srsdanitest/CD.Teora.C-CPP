//
// CmnHdr.h
// Purpose:  Common header file containing macros and definitions used
// throughout all applications in the book

// Disable warnings so that code will compile cleanly using warning level 4.

// nonstandard extension 'single line comment' was used
#pragma warning(disable: 4001)
// nonstandard extension used : nameless struc/union
#pragma warning(disable: 4201)
// nonstandard extension used : bit field types other than int
#pragma warning(disable: 4214)
// Note:  creating pre-compiled header
#pragma warning(disable: 4699)
// unreferenced inline function has been removed
#pragma warning(disable: 4514)
// unreferenced formal parameter
#pragma warning(disable: 4100)
// indirection to slightly different base types
#pragma warning(disable: 4057)
// named type definition in parentheses
#pragma warning(disable: 4115)
// nonstandard extension used : benign typedef redefinition
#pragma warning(disable: 4209)

// Windows Version build option
#define _WIN32_WINNT 0x0400
// Strict build option: Force all EXE/DLL to use STRICT type checking
#define STRICT

// CPU Portability Macros

// If no CPU platform was specified, default to the current platform
#if !defined(_PPC_) && !defined(_ALPHA_) && !defined(_MIPS_) && !defined(_X86_)
	#if defined(_M_IX86_)
   	#define _X86_
   #endif
   #if defined(_M_MRX000)
   	#define _MIPS)
   #endif
   #if defined(_M_ALPHA)
   	#define _ALPHA_
   #endif
   #if defined(_M_PPC)
   	#define _PPC_
   #endif
#endif

// Unicode build option

// If you are not compiling for an x86 CPU, you always compile using Unicode.
#ifndef _X86_
	#define UNICODE
#endif

// To compile using Unicode on the x86 CPU, uncomment the line below:
// #define UNICODE

// When using Unicode win32 functions, use Unicode C-Runtime functions too.
#ifdef UNICODE
	#define _UNICODE
#endif

// chDIMOF Macro

// This macro evaluates to the number of elements in an array.
#define chDIMOF(Array) (sizeof(Array) / sizeof(Array[0]))

// chBEGINTHREADEX Macro

// Create a chBEGINTHREADEX macro that calls the C run-time's
// _beginthreadex function.  The C run-time library doesn't
// want to have any reliance on Win32 data types such as HANDLE.
// This means that a Win32 progammer needs to case the return value
// to a HANDLE, which is inconvenient. This macro will perform the
// casting for you:
typedef unsigned (_stdcall *PTHREAD_START) (void *);
	#define chBEGINTHREADEX(lpsa, cbStack, lpStartAddr, \
   	lpvthreadParm, fdwCreate, lpIDThread)            \
      ((HANDLE)_beginthreadex                          \
         (                                             \
      	(void *) (lpsa), (unsigned) (cbStack),        \
         (PTHREAD_START) (lpStartAddr),                \
         (void *) (lpvThreadParm),                     \
         (unsigned) (fdwCreate),                       \
         (unsigned *) (lpIDThread))                    \
         )

// Assert/Verify macros
#define chFAIL(szMSG)                                              \
{                                                                  \
	MessageBox(GetActiveWindow(), szMSG, _TEXT("Assertion Failed"), \
   MB_OK | MB_ICONERROR);                                          \
   DebugBreak();                                                   \
}

// Put up an assertion failure message box.
#define chASSERTFAIL(file, line, expr)               \
{                                                    \
	TCHAR sz[128];                                    \
   wsprintf(sz, _TEXT("File %hs, line %d : %hs"),    \
   	file, line, expr);                             \
   chFAIL(sz);                                       \
}

// Put up a message box if an assertion filas in a debug build.
#ifdef _DEBUG
#define chASSERT(x) if (!(x))			 \
	chASSERTFAIL(__FILE__, __LINE__, #x)
#else
#define chASSERT(x)
#endif

// Assert in debug builds. Don't remove the code in retail builds.
#ifdef _DEBUG
#define chVERIFY(x) chASSERT(x)
#else
#define chVERIFY(x) (x)
#endif

// chHANDLE_DLGMSG Macro

// The normal HANDLE_MSG macro in WINDOWSX.H does not work
// properly for dialog boxes because DlgProcs return a BOOL
// instead of an LRESULT (like WndProcs). This chHANDLE_DLGMSG
// macro will correct the problem:
#define chHANDLE_DLGMSG(hwnd, message, fn)                                   \
  case (message):                                                            \
    return (SetDlgMsgResult(hwnd, uMsg, HANDLE_##message((hwnd), (wParam), (lParam), (fn))))

// Quick MesageBox Macro
#define chMB(s)														\
	{                                                     \
   TCHAR szTMP[128];                                     \
   GetModuleFileName(NULL, szTMP, chDIMOF(szTMP));       \
   MessageBox(GetActiveWindow(), s, szTMP, MB_OK);       \
   }

// Zero Variable Macro
// Zero out a structure. If fInitsize is TRUE, initialize the first
// int to the size of the structure. Many structures like WNDCLASSEX and
// STARUPINFO require that their first member be set to the size of the
// structure itself.
#define chINITSTRUCT(structure, fInitSize)                     \
	(ZeroMemory(&(structure), sizeof(structure)),               \
   fInitSize ? (*(int*) &(structure) = sizeof(structure)) : 0)

// Dialog Box Icon Setting Macro
// The call to SetClassLong is for Windows NT 3.51 or less.
// The WM_SETICON messages are for Windows NT 4.0 and Win 95.
#define chSETDLGICONS(hwnd, idiLarge, idiSmall)                 \
	{                                                            \
   	OSVERSIONINFO VerInfo;                                    \
      chINITSTRUCT(VerInfo, TRUE);                              \
      GetVersionEx(&VerInfo);                                   \
      if ((VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) &&    \
      	(VerInfo.dwMajorVersion <= 3 &&                        \
         VerInfo.dwMinorVersion <= 51))                         \
         {                                                      \
         SetClassLong(hwnd, GCL_HICON, (LONG)                   \
         	LoadIcon(GetWindowInstance(hwnd),                   \
            MAKEINTRESOURCE(idiLarge)));                        \
         }                                                      \
      else                                                      \
      	{                                                      \
         SendMessage(hwnd, WM_SETICON, TRUE, (LPARAM)           \
         	LoadIcon(GetWindowInstance(hwnd),                   \
            MAKEINTRESOURCE(idiLarge)));                        \
         SendMessage(hwnd, WM_SETICON, FALSE, (LPARAM)          \
         	LoadIcon(GetWindowInstance(hwnd),                   \
            MAKEINTRESOURCE(idiSmall)));                        \
         }                                                      \
   }

// UNICODE check Macro
#ifdef UNICODE
#define chWARNIFUNICODEUNDERWIN95()                                         \
	if (GetWindowsDirectoryW(NULL, 0) <= 0)                                  \
   	MessageBoxA(NULL, "This operating system does not support UniCode.",  \
      NULL, MB_OK)
#else
#define chWARNIFUNICODEUNDERWIN95()
#endif

// Pragma message helper macro
// When the compiler sees a line like:  #pragma chMSG(Fix this later)
// it will output a line like this: C:\Document=AdvWin.....fix this later.
// you can easily jump directly to this line and examine the surrounding code.
#define chSTR(x) #x
#define chSTR2(x) chSTR(x)
#define chMSG(desc)											\
	message(_FILE_ "(" chSTR2(_LINE_) "):" #desc)

