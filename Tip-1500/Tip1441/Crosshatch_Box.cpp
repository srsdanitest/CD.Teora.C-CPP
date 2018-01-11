
#include <windows.h>  
#include "Crosshatch_Box.h" 


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
static HENHMETAFILE hMetaFile = NULL;

   switch( uMsg )
   {
      case WM_CREATE  : 
              {
                 HDC  hMetaDC;
                 HDC  hRefDC;
                 RECT rect;
                 int  iWidthMM, iHeightMM, iWidthPels, iHeightPels;
                 int  iMMPerPelX, iMMPerPelY;

                 hRefDC = GetDC( hWnd );

                 // Compute the size of the client area in 0.01 mm.
                 //................................................
                 iWidthMM    = GetDeviceCaps(hRefDC, HORZSIZE);
                 iHeightMM   = GetDeviceCaps(hRefDC, VERTSIZE);
                 iWidthPels  = GetDeviceCaps(hRefDC, HORZRES);
                 iHeightPels = GetDeviceCaps(hRefDC, VERTRES);

                 iMMPerPelX = (iWidthMM * 100)/iWidthPels;
                 iMMPerPelY = (iHeightMM * 100)/iHeightPels;

                 GetClientRect(hWnd, &rect);

                 rect.right = rect.right * iMMPerPelX;
                 rect.bottom = rect.bottom * iMMPerPelY;
      
                 // Create an enhanced metafile.
                 //.............................
                 hMetaDC = CreateEnhMetaFile( hRefDC, NULL, &rect, 
                                              "Test Metafile" );

                 // Draw on the metafile.
                 //......................
                 if ( hMetaDC )
                 {
                    HBRUSH hBrush;

                    GdiComment( hMetaDC, 23, "This is for an example." );
                    hBrush = CreateHatchBrush( HS_DIAGCROSS, RGB(0, 0, 255) );

                    SelectObject( hMetaDC, hBrush );
                    Rectangle( hMetaDC, 10, 10, 200, 200 );

                    hMetaFile = CloseEnhMetaFile( hMetaDC );
                    DeleteObject( hBrush );
                 }
               
                 ReleaseDC( hWnd, hRefDC );
              }
              break;

      case WM_PAINT   : 
              {
                 PAINTSTRUCT ps;
                 RECT        rect;

                 BeginPaint( hWnd, &ps );

                 GetClientRect( hWnd, &rect );
                 PlayEnhMetaFile( ps.hdc, hMetaFile, &rect );

                 EndPaint( hWnd, &ps );
              }
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_ABOUT :
                        DialogBox( hInst, "AboutBox", hWnd, (DLGPROC)About );
                        break;

                 case IDM_EXIT :
                        DestroyWindow( hWnd );
                        break;
              }
              break;
      
      case WM_DESTROY :
              DeleteEnhMetaFile( hMetaFile );
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
