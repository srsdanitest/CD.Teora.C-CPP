
#include <windows.h>  
#include "Virtual_Allocate.h" 


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

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static LPVOID lpMem = NULL;

   switch( uMsg )
   {
      case WM_CREATE  : 
              // Reserve 1MB of virtual memory.
              //...............................
              lpMem = VirtualAlloc( NULL, 1048576, MEM_RESERVE, 0 );
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        {
                           // Commit a 70KB block of memory from virtual
                           // memory then use it.
                           //...........................................
                           DWORD  dwoldAccess;
                           LPTSTR lpBuf = VirtualAlloc( lpMem, 71680,
                                                  MEM_COMMIT, PAGE_READWRITE );
                           
                           // Set each 1KB block of memory to a number.
                           //..........................................
                           if ( lpBuf )
                           {
                              int i;
                              for( i = 0; i < 70; i++ )
                              {
                                 if ( VirtualLock( (lpBuf+(i*1024)), 1024 ) )
                                 {
                                    memset( (lpBuf+(i*1024)), i, 1024 );
                                    VirtualUnlock( (lpBuf+(i*1024)), 1024 );
                                 } 
                              } 
                           }

                           // Protect the memory with Read-Only access.
                           //..........................................
                           VirtualProtect( lpBuf, 71680, PAGE_READONLY,
                                           &dwoldAccess );

                           __try // to read from the memory.
                           {
                              char szMsg[20];

                              wsprintf( szMsg, "Memory Value = %d",
                                        *(lpBuf+2048) );
                              MessageBox( hWnd, szMsg, "Read", 
                                          MB_OK | MB_ICONINFORMATION );
                           }
                           __except( 1 )
                           {
                              MessageBox( hWnd, "Error accessing memory",
                                         "Read", 
                                          MB_OK | MB_ICONEXCLAMATION );
                           }

                           __try  // to write to the memory.
                           {
                              *lpBuf = 10;
                           }
                           __except( 1 )
                           {
                              MessageBox( hWnd, "Error accessing memory", 
                                         "Write", 
                                          MB_OK | MB_ICONEXCLAMATION );
                           }
                        }
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
              // Free virtual memory.
              //.....................
              VirtualFree( lpMem, 0, MEM_RELEASE );  
              PostQuitMessage(0);
              break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}


LRESULT CALLBACK About( HWND hDlg,           
                        UINT message,        
                        WPARAM wParam,       
                        LPARAM lParam)
{
   switch (message) 
   {
       case WM_INITDIALOG: 
               return (TRUE);

       case WM_COMMAND:                              
               if (   LOWORD(wParam) == IDOK         
                   || LOWORD(wParam) == IDCANCEL)    
               {
                       EndDialog(hDlg, TRUE);        
                       return (TRUE);
               }
               break;
   }

   return (FALSE); 
}
