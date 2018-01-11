
#include <windows.h>  
#include "Enum_AllFonts.h" 


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

int CALLBACK EnumFontProc( ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, 
                           int nFontType, LPARAM lParam )
{

   // Load only TrueType fonts into the list box.
   //............................................
   if ( nFontType & TRUETYPE_FONTTYPE )
   {
      if ( IsWindow( (HWND)lParam ) )
      {
         SendMessage( (HWND)lParam, LB_ADDSTRING, 0, 
                      (LPARAM)lpelf->elfLogFont.lfFaceName );
      }
   }

   return( TRUE );
}


int CALLBACK FindFontProc( ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, 
                           int nFontType, LPARAM lParam )
{
   // Find the regular font.
   //.......................
   if ( strcmp( lpelf->elfStyle, "Regular" ) == 0 )
      memcpy( (LOGFONT*)lParam, &lpelf->elfLogFont, sizeof( LOGFONT ) );

   return( TRUE );
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static HWND hList;

   switch( uMsg )
   {
      case WM_CREATE  :
              {
                 HDC hDC;

                 // Create a list box and fill it with the
                 // available TrueType font names.
                 //.......................................              
                 hList = CreateWindow( "LISTBOX", "", 
                                    WS_CHILD | WS_VISIBLE | LBS_STANDARD,
                                    0, 0, 200, 200, hWnd, (HMENU)101, hInst,
                                    NULL );

                 hDC = GetDC( hWnd );
                 EnumFontFamilies( hDC, NULL, EnumFontProc,(LPARAM)hList );
                 ReleaseDC( hWnd, hDC );

                 SendMessage( hList, LB_SETCURSEL, 0, 0 );
              }
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        {
                           HDC     hDC;
                           LOGFONT lf;
                           HFONT   hFont;
                           char    szFaceName[128];
                           int     nSel;

                           // Retrieve the currently selected font name.
                           //...........................................
                           nSel = SendMessage( hList, LB_GETCURSEL, 0, 0 );
                           SendMessage( hList, LB_GETTEXT, nSel,
                                        (LPARAM)szFaceName );

                           // Repaint the client area of the window.
                           //.......................................
                           InvalidateRect( hWnd, NULL, TRUE );
                           UpdateWindow( hWnd );

                           // Find the selected font and retrieve the
                           // LOGFONT structure for the font.
                           //.........................................
                           hDC = GetDC( hWnd );
                           EnumFontFamilies( hDC, szFaceName,
                                             FindFontProc,(LPARAM) &lf );

                           // Create the font and output a sample text string.
                           //.................................................
                           hFont = CreateFontIndirect( &lf );
                           SelectObject( hDC, hFont );

                           TextOut( hDC, 10, 230, "Sample Text Output.", 19 );

                           ReleaseDC( hWnd, hDC );
                           DeleteObject( hFont );
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
