
#include <windows.h>  
#include "Global_Realloc.h" 


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
static PAINTSTRUCT ps;
static char        szBuf[128];
static LPTSTR      pMem = NULL;

   switch( uMsg )
   {
      case WM_CREATE :
              {
                 // Allocate Initial block of memory and
                 // Initialize it with the alphabet in uppercase.
                 //..............................................
                 HGLOBAL hMem = GlobalAlloc( GHND, 27 );
                 LPTSTR  pCur;

                 if ( hMem && (pMem = (LPTSTR)GlobalLock( hMem )) != NULL )
                 {
                    int i;

                    pCur = pMem;
                    for( i=0; i<26; i++ )
                        *pCur++ = 'A'+i;

                    *pCur = 0;
                 }
                 else
                 {
                    MessageBox( hWnd, "Could not allocate memory", 
                                "Memory Error", 
                                MB_OK | MB_ICONSTOP );

                    DestroyWindow( hWnd );
                 }
              }
              break;

      case WM_PAINT :
              // Paint the status of the memory.
              //................................
              BeginPaint( hWnd, &ps );
              if( pMem )
              {
                 // Retrieve the handle for
                 // the memory and memory status.
                 //..............................
                 HGLOBAL hMem   = GlobalHandle( pMem );
                 DWORD   dwSize = GlobalSize( hMem );
                 UINT    uFlags = GlobalFlags( hMem );

                 TextOut( ps.hdc, 10, 10, szBuf, wsprintf( szBuf,
                         "The memory block is %ld bytes in size.", dwSize ) );
                 TextOut( ps.hdc, 10, 30, szBuf, wsprintf( szBuf, 
                          "Contains: %s", pMem ) );
                 TextOut( ps.hdc, 10, 50, szBuf, wsprintf( szBuf,
                          "Flags: Discardable=%d, Lock Count=%d",
                          uFlags & GMEM_DISCARDABLE, 
                          uFlags & GMEM_LOCKCOUNT ) );
              }
              EndPaint( hWnd, &ps );
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        // ReAllocate memory and add the 
                        // lowercase alphabet to the memory.
                        //..................................
                        if ( pMem )
                        {
                           HGLOBAL hMem = GlobalHandle( pMem );

                           GlobalUnlock( hMem );
                           pMem = NULL;

                           hMem = GlobalReAlloc( hMem, (26*2)+1, 
                                                 GMEM_MOVEABLE );
                           if ( hMem )
                           {
                              LPTSTR pCur;
                              int    i;

                              pMem = (LPTSTR)GlobalLock( hMem );

                              // Skip the old values.
                              //.....................
                              pCur = pMem+26;                  

                              // Set the new values.
                              //....................
                              for( i=0; i<26; i++ )
                                 *pCur++ = 'a'+i;

                              *pCur = 0;
                           }
                           else
                              MessageBox( hWnd, "Could not allocate memory",
                                         "Memory Error", 
                                          MB_OK | MB_ICONSTOP );

                           InvalidateRect( hWnd, NULL, TRUE );
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
              if ( pMem )
              {
                 HGLOBAL hMem = GlobalHandle( pMem );

                 GlobalUnlock( hMem );
                 GlobalFree( hMem );
              }
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
