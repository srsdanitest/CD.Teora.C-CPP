
#include <windows.h>  
#include "Sample_Map.h" 


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

DWORD AnotherProcess( LPDWORD lpdwParam )
{
   HANDLE hFileMap;    
   LPTSTR lpMapAddress; 

   // Open the file mapping.
   //.......................
   hFileMap = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, 
                               "MyFileMappingObject" );

   // Map a view to the mapping object.
   //..................................
   lpMapAddress = MapViewOfFileEx( hFileMap, FILE_MAP_ALL_ACCESS, 
                                 0, 0, 0, lpdwParam);

   // Display the contents of the memory.
   //....................................
   MessageBox( NULL, lpMapAddress, "Mapped Memmory", 
               MB_OK | MB_ICONINFORMATION );

   // Set "Received" into the memory.
   //................................
   strcpy( lpMapAddress, "Received" );

   UnmapViewOfFile( lpMapAddress );

   return( 0 );
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static HANDLE hMapFile = NULL;
static HANDLE hThread  = NULL;
static LPTSTR lpMapAddress = NULL;

   switch( uMsg )
   {
      case WM_CREATE :
              // Create a file mapped object.
              //.............................
              hMapFile = CreateFileMapping( (HANDLE)0xFFFFFFFF, NULL,
                                            PAGE_READWRITE,
                                            0,
                                            1024,
                                           "MyFileMappingObject" );

              // Return if the mapping failed.
              //..............................
              if ( !hMapFile )
                 return(-1);

              break;


      case WM_TIMER :
              // Check to see if the thread has processed the memory.
              //.....................................................
              if ( strcmp( lpMapAddress, "Received" ) == 0 )
              {
                 // Kill the timer and thread.
                 //...........................
                 KillTimer( hWnd, 1 );
                 TerminateThread( hThread, 0 );

                 // Show the mapped data and unmap the view.
                 //.........................................
                 MessageBox( hWnd, lpMapAddress, "Done", MB_OK );

                 UnmapViewOfFile( lpMapAddress );
              }
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        {
                           DWORD  dwID;

                           // Map a view of the file mapped object.
                           //......................................
                           lpMapAddress = MapViewOfFile( hMapFile, 
                                                         FILE_MAP_ALL_ACCESS, 
                                                         0, 0, 0);

                           // Place data in the view.
                           //........................
                           strcpy( lpMapAddress, 
                                   "Data passed from main process." );

                           // Make sure the data is flushed to the file.
                           //...........................................
                           FlushViewOfFile( lpMapAddress, 
                                            lstrlen( lpMapAddress ) );

                           // Create a thread to receive the data.
                           //.....................................
                           hThread = CreateThread( NULL, 0, 
                                      (LPTHREAD_START_ROUTINE)AnotherProcess,
                                      lpMapAddress, 0, &dwID );

                           // Set a timer to wait for the data to be processed.
                           //..................................................
                           SetTimer( hWnd, 1, 1000, NULL );
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
              CloseHandle( hMapFile );

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
