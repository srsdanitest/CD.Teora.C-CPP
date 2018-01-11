
#include <windows.h>  
#include "Scroll_DC.h" 


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

VOID Scroll( HWND hWnd, int* pnCurPos, WORD wScroll )
{
   int nMin, nMax;
   int nPos;

   // Retrieve the scroll information of the scroll bar.
   //...................................................
   GetScrollRange( hWnd, SB_HORZ, &nMin, &nMax );
   nPos = GetScrollPos( hWnd, SB_HORZ );

   switch( wScroll )
   {
      // Scroll to the right.
      //.....................
      case SB_LINERIGHT :
             if ( *pnCurPos < nMax )
               *pnCurPos += 1;
             break;

      // Scroll to the left.
      //....................
      case SB_LINELEFT :
             if ( *pnCurPos > 0 )
                *pnCurPos -= 1;
             break;
   }

   // If the position has changed,
   // actually scroll the window.
   //.............................
   if ( nPos != *pnCurPos )
   {
      RECT cltRect;
      HDC  hDC  = GetDC( hWnd );

      GetClientRect( hWnd, &cltRect );
      cltRect.left   += 20;
      cltRect.right  -= 20;
      cltRect.top    += 20;
      cltRect.bottom -= 20;

      ScrollDC( hDC, (*pnCurPos-nPos)*20, 0, NULL, &cltRect, 
                NULL, NULL );

      SetScrollPos( hWnd, SB_HORZ, *pnCurPos, TRUE );
   }
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static int  nCurPos   = 0;

   switch( uMsg )
   {
      case WM_CREATE :
              ShowScrollBar( hWnd, SB_HORZ, FALSE );
              SetScrollRange( hWnd, SB_HORZ, 0, 10, FALSE );
              SetScrollPos( hWnd, SB_HORZ, 0, TRUE );
              break;

      case WM_HSCROLL :
              Scroll( hWnd, &nCurPos, LOWORD( wParam ) );
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        {
                           HDC  hDC  = GetDC( hWnd );
                           RECT rect;
                           int  i;

                           // Paint vertical lines in client area.
                           //.....................................
                           GetClientRect( hWnd, &rect );

                           for( i=0; i<20; i++ )
                           {
                              MoveToEx( hDC, i*8, 0, NULL );
                              LineTo( hDC, i*8, rect.bottom );
                           }

                           ReleaseDC( hWnd, hDC );
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
