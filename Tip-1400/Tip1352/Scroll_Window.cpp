
#include <windows.h>  
#include "Scroll_Window.h" 


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
                        WS_OVERLAPPEDWINDOW | WS_VSCROLL, 
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
   SCROLLINFO si;

   // Use GetScrollInfo() to get information
   // about the scroll bar.
   //.......................................
   si.cbSize = sizeof( SCROLLINFO );
   si.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS;
   GetScrollInfo( hWnd, SB_VERT, &si );

   switch( wScroll )
   {
      case SB_LINEDOWN :
              if ( *pnCurPos <= (int)(si.nMax - si.nPage) )
                 *pnCurPos += 1;
              break;

      case SB_LINEUP :
              if ( *pnCurPos > 0 )
                 *pnCurPos -= 1;
              break;
   }

   if ( si.nPos != *pnCurPos )
   {
      RECT cltRect;

      GetClientRect( hWnd, &cltRect );

      ScrollWindowEx( hWnd, 0, (si.nPos-*pnCurPos)*20, NULL,
                     &cltRect, NULL, NULL, SW_INVALIDATE );

      si.fMask = SIF_POS;
      si.nPos  = *pnCurPos;
      SetScrollInfo( hWnd, SB_VERT, &si, TRUE );
   }
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static int  nDspLines;
static int  nNumItems = 0;
static int  nCurPos   = 0;
static char szBuf[10];

   switch( uMsg )
   {
      case WM_CREATE :
              ShowScrollBar( hWnd, SB_VERT, TRUE );
              break;

         // Every time the window is sized, re-calculate the number of lines
         // the client area can display and set the scroll bar accordingly.
         //................................................................
      case WM_SIZE :
              {
                 RECT rect;
                 GetClientRect( hWnd, &rect );

                 nDspLines = rect.bottom / 20;

                 if ( nDspLines < nNumItems ) 
                 {
                    SCROLLINFO si;

                    si.cbSize = sizeof( SCROLLINFO );
                    si.fMask  = SIF_POS | SIF_RANGE | SIF_PAGE;
                    si.nMin   = 0;
                    si.nMax   = nNumItems-1;
                    si.nPage  = nDspLines;
                    si.nPos   = nCurPos;

                    EnableScrollBar( hWnd, SB_VERT, ESB_ENABLE_BOTH );
                    SetScrollInfo( hWnd, SB_VERT, &si, TRUE );
                 }
                 else
                    EnableScrollBar( hWnd, SB_VERT, ESB_DISABLE_BOTH );
              }
              break;
               
      case WM_PAINT :
              {
                 PAINTSTRUCT ps;
                 int         i,j;
                 int         nNumPaint;

                 nNumPaint = min( nCurPos+nDspLines, nNumItems );

                 BeginPaint( hWnd, &ps );

                 for ( j=0,i=nCurPos; i<nNumPaint; i++,j++ )
                 {
                    itoa( i, szBuf, 10 );
                    TextOut( ps.hdc, 10, j*20, "Line of Text:", 13 );
                    TextOut( ps.hdc, 90, j*20, szBuf, strlen( szBuf ) );
                 }
                  
                 EndPaint( hWnd, &ps );
              }
              break;

      case WM_VSCROLL :
              Scroll( hWnd, &nCurPos, LOWORD( wParam ) );
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        if ( nDspLines == nNumItems ) 
                           EnableScrollBar( hWnd, SB_VERT, ESB_ENABLE_BOTH );

                        nNumItems++;
                        if ( nDspLines < nNumItems )
                        {
                           SCROLLINFO si;

                           si.cbSize = sizeof( SCROLLINFO );
                           si.fMask  = SIF_RANGE | SIF_PAGE;
                           si.nMin   = 0;
                           si.nMax   = nNumItems-1;
                           si.nPage  = nDspLines;

                           SetScrollInfo( hWnd, SB_VERT, &si, TRUE );
                        }

                        InvalidateRect( hWnd, NULL, FALSE );
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
