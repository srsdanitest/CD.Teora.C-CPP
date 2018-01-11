
#include <windows.h>  
#include "EnumResT.h" 


#if defined (WIN32)
	#define IS_WIN32 TRUE
#else
	#define IS_WIN32 FALSE
#endif

#define IS_NT      IS_WIN32 && (BOOL)(GetVersion() < 0x80000000)
#define IS_WIN32S  IS_WIN32 && (BOOL)(!(IS_NT) && (LOBYTE(LOWORD(GetVersion()))<4))
#define IS_WIN95   (BOOL)(!(IS_NT) && !(IS_WIN32S)) && IS_WIN32

HINSTANCE hInst;   // current instance

LPCTSTR lpszAppName  = "MyApp";
LPCTSTR lpszTitle    = "My Application"; 

BOOL RegisterWin95( CONST WNDCLASS* lpwc );

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine, int nCmdShow)
{
   MSG      msg;
   HWND     hWnd; 
   WNDCLASS wc;

   // Register the main application window class.
   //............................................
   wc.style         = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc   = (WNDPROC)WndProc;       
   wc.cbClsExtra    = 0;                      
   wc.cbWndExtra    = 0;                      
   wc.hInstance     = hInstance;              
   wc.hIcon         = LoadIcon( hInstance, lpszAppName ); 
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   wc.lpszMenuName  = lpszAppName;              
   wc.lpszClassName = lpszAppName;              

   if ( IS_WIN95 )
   {
      if ( !RegisterWin95( &wc ) )
         return( FALSE );
   }
   else if ( !RegisterClass( &wc ) )
      return( FALSE );

   hInst = hInstance; 

   // Create the main application window.
   //....................................
   hWnd = CreateWindow( lpszAppName, 
                        lpszTitle,    
                        WS_OVERLAPPEDWINDOW, 
                        CW_USEDEFAULT, 0, 
                        CW_USEDEFAULT, 0,  
                        NULL,              
                        NULL,              
                        hInstance,         
                        NULL               
                      );

   if ( !hWnd ) 
      return( FALSE );

   ShowWindow( hWnd, nCmdShow ); 
   UpdateWindow( hWnd );         

   while( GetMessage( &msg, NULL, 0, 0) )   
   {
      TranslateMessage( &msg ); 
      DispatchMessage( &msg );  
   }

   return( msg.wParam ); 
}


BOOL RegisterWin95( CONST WNDCLASS* lpwc )
{
   WNDCLASSEX wcex;

   wcex.style         = lpwc->style;
   wcex.lpfnWndProc   = lpwc->lpfnWndProc;
   wcex.cbClsExtra    = lpwc->cbClsExtra;
   wcex.cbWndExtra    = lpwc->cbWndExtra;
   wcex.hInstance     = lpwc->hInstance;
   wcex.hIcon         = lpwc->hIcon;
   wcex.hCursor       = lpwc->hCursor;
   wcex.hbrBackground = lpwc->hbrBackground;
   wcex.lpszMenuName  = lpwc->lpszMenuName;
   wcex.lpszClassName = lpwc->lpszClassName;

   // Added elements for Windows 95.
   //...............................
   wcex.cbSize = sizeof(WNDCLASSEX);
   wcex.hIconSm = LoadImage(wcex.hInstance, lpwc->lpszClassName, 
                            IMAGE_ICON, 16, 16,
                            LR_DEFAULTCOLOR );
			
   return RegisterClassEx( &wcex );
}


BOOL CALLBACK ListResourceTypes( HANDLE hModule, LPTSTR lpszType, LONG lParam )
{
   LPTSTR lpAddString = lpszType;
   HWND   hListBox    = (HWND)lParam;

   // Check to see if the resource type is a pre-defined type. If it is
   // set lpAddString to a descriptive string.
   //.........................................
   switch( LOWORD(lpszType) )
   {
      case RT_ACCELERATOR   : lpAddString = "Accelerator"; break;
      case RT_BITMAP        : lpAddString = "Bitmap"; break;
      case RT_DIALOG        : lpAddString = "Dialog"; break;
      case RT_FONT          : lpAddString = "Font"; break;
      case RT_FONTDIR       : lpAddString = "FontDir"; break;
      case RT_MENU          : lpAddString = "Menu"; break;
      case RT_RCDATA        : lpAddString = "RC Data"; break;
      case RT_STRING        : lpAddString = "String Table"; break;
      case RT_MESSAGETABLE  : lpAddString = "Message Table"; break;
      case RT_CURSOR        : lpAddString = "Cursor"; break;
      case RT_GROUP_CURSOR  : lpAddString = "Group Cursor"; break;
      case RT_ICON          : lpAddString = "Icon"; break;
      case RT_GROUP_ICON    : lpAddString = "Group Icon"; break;
      case RT_VERSION       : lpAddString = "Version Information"; break;
   }

   SendMessage( hListBox, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)lpAddString );

   return( TRUE ); 
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static HWND hListBox = NULL;

   switch( uMsg )
   {
      case WM_CREATE : 
               hListBox = CreateWindow( "LISTBOX", "",
                                       WS_CHILD | WS_BORDER |
                                       WS_VISIBLE | LBS_STANDARD,
                                       10, 10, 250, 100,
                                       hWnd, (HMENU) 101,  
                                       hInst, NULL );
               break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        EnumResourceTypes( hInst, ListResourceTypes,
                                           (LONG)hListBox );
                        break;

                 case IDM_ABOUT :
                        DialogBox( hInst, "AboutBox", hWnd, (DLGPROC)About );
                        break;

                 case IDM_EXIT :
                        DestroyWindow( hWnd );
                        break;
              }
              break;
      
      case WM_DESTROY :
              PostQuitMessage(0);
              break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}


LRESULT CALLBACK About( HWND hDlg,           // window handle of the dialog box
                        UINT message,        // type of message
                        WPARAM wParam,       // message-specific information
                        LPARAM lParam)
{
   switch (message) 
   {
       case WM_INITDIALOG:  // message: initialize dialog box
               {
                  LPSTR   lpVersion;       
                  DWORD   dwVerInfoSize;
                  DWORD   dwVerHnd;
                  UINT    uVersionLen;
                  WORD    wRootLen;
                  BOOL    bRetCode;
                  int     i;
                  char    szFullPath[256];
                  char    szResult[256];
                  char    szGetName[256];

                  // Get version information from the application
                  //.............................................
                  GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));
                  dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
                  if (dwVerInfoSize) 
                  {
                       // If we were able to get the information, process it:
                       //....................................................
                       LPSTR   lpstrVffInfo;

                       lpstrVffInfo  = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwVerInfoSize );
                       GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);
                       strcpy(szGetName, "\\StringFileInfo\\040904B0\\");
                       wRootLen = strlen(szGetName);

                       // Walk through the dialog items that we want to replace:
                       //.......................................................
                       for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++) 
                       {
                           GetDlgItemText(hDlg, i, szResult, sizeof(szResult));
                           szGetName[wRootLen] = (char)0;
                           strcat (szGetName, szResult);
                           uVersionLen   = 0;
                           lpVersion     = NULL;
                           bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
                                                          (LPSTR)szGetName,
                                                          (LPVOID)&lpVersion,
                                                          (LPDWORD)&uVersionLen); 

                           if ( bRetCode && uVersionLen && lpVersion) 
                           {
                                 // Replace dialog item text with version info
                                 lstrcpy(szResult, lpVersion);
                                 SetDlgItemText(hDlg, i, szResult);
//                                 SendMessage (GetDlgItem (hDlg, i), WM_SETFONT, (UINT)hfontDlg, TRUE);
                           }
                       } // for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++)

                       HeapFree( GetProcessHeap(), 0, lpstrVffInfo );
                  } // if (dwVerInfoSize)
               }
               return (TRUE);

       case WM_COMMAND:                              // message: received a command
               if (   LOWORD(wParam) == IDOK         // "OK" box selected?
                   || LOWORD(wParam) == IDCANCEL)    // System menu close command?
               {
                       EndDialog(hDlg, TRUE);        // Exit the dialog
                       return (TRUE);
               }
               break;
   }

   return (FALSE); 
}
