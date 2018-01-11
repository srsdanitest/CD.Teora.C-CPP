
#include <windows.h>  
#include "Change_Colors.h"


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

#define ALIGNLONG(i) ((i+3)/4*4)
#define WIDTH        50
#define HEIGHT       50
#define COLORBITS    4


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static HBITMAP            hBitmap;
static LPBITMAPINFOHEADER lpbi;
static BITMAPINFOHEADER   bi;

   switch( uMsg )
   {
      case WM_CREATE :
               {
                  HDC    hDC, hMemDC;
                  LPTSTR lpstBitmap;

                  hDC = GetDC (hWnd) ;
                  
                  // Intialize BITMAPINFOHEADER data.
                  //.................................
                  bi.biSize     = sizeof (BITMAPINFOHEADER) ;
                  bi.biWidth    = WIDTH;     
                  bi.biHeight   = HEIGHT;
                  bi.biPlanes   = 1;
                  bi.biBitCount = COLORBITS;
                  bi.biCompression = BI_RGB;
                  bi.biSizeImage = ( ALIGNLONG( (WIDTH * COLORBITS)/8 ) 
                                         * HEIGHT);
                  bi.biXPelsPerMeter = 0;
                  bi.biYPelsPerMeter = 0;
                  bi.biClrUsed       = 0;
                  bi.biClrImportant  = 0;

                  // Create uninitialized DIB bitmap.
                  //.................................
                  hBitmap = CreateDIBitmap( hDC, &bi, 0L, NULL, 
                                            NULL, 0);

                  // Allocate memory for BITMAPINFO structure.
                  //..........................................
                  lpbi = (BITMAPINFOHEADER*)GlobalAlloc( GPTR, 
                                       sizeof(BITMAPINFOHEADER) +
                                       16 * sizeof (RGBQUAD) + 
                                       (ALIGNLONG((WIDTH * COLORBITS)/8)
                                       * HEIGHT) );
                  
                  // Copy BITMAPINFOHEADER information.
                  //...................................
                  *lpbi = bi;
                  
                  // Initialize structure data with GetDIBits().
                  //............................................
                  GetDIBits( hDC, hBitmap, 0, 50, NULL, 
                            (LPBITMAPINFO) lpbi, DIB_RGB_COLORS);
                  
                  // Create memory device context and select bitmap.
                  //................................................
                  hMemDC = CreateCompatibleDC( hDC );
                  
                  SelectObject( hMemDC, hBitmap );
                  
                  // Paint on memory device context.
                  //................................
                  SelectObject( hMemDC, GetStockObject(BLACK_BRUSH) );
                  Rectangle (hMemDC, 0, 0, WIDTH, HEIGHT);

                  SelectObject( hMemDC, GetStockObject(WHITE_BRUSH) ) ;
                  Ellipse( hMemDC, 0, 0, WIDTH, HEIGHT );
                  MoveToEx( hMemDC, 0, 0, NULL );
                  LineTo( hMemDC, WIDTH / 2, HEIGHT / 2 );
                  LineTo( hMemDC, WIDTH, 0 );
                  
                  // Set pointer to bitmap’s bit data.
                  //..................................
                  lpstBitmap = (LPSTR)lpbi + (WORD)sizeof(BITMAPINFOHEADER) +
                                             (16 * sizeof(RGBQUAD));

                  GetDIBits( hDC, hBitmap, 0, HEIGHT, lpstBitmap,
                             (LPBITMAPINFO) lpbi, DIB_RGB_COLORS);

                  DeleteDC( hMemDC );
                  ReleaseDC( hWnd, hDC);
               }
               break;

      case WM_PAINT :
               {
                  PAINTSTRUCT ps;
                  HDC         hMemDC;

                  BeginPaint( hWnd, &ps );
                  hMemDC = CreateCompatibleDC( ps.hdc );

                  SelectObject( hMemDC, hBitmap );
                  BitBlt( ps.hdc, 10, 10, WIDTH, HEIGHT, 
                          hMemDC, 0, 0, SRCCOPY );

                  DeleteDC( hMemDC );
                  EndPaint( hWnd, &ps );
               }
               break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        { 
                           HDC    hDC;
                           int    nBytes, i;
                           LPTSTR lpstBitmap, lpstTemp;

                           hDC = GetDC( hWnd );

                           lpstBitmap = (LPSTR)lpbi + 
                                        (WORD) sizeof(BITMAPINFOHEADER) +
                                         (16 * sizeof (RGBQUAD));

                           nBytes = ALIGNLONG((WIDTH * COLORBITS)/8) 
                                    * HEIGHT;

                           lpstTemp = lpstBitmap;
                  
                           // Change 0 bytes to 0x2C in bitmap data.
                           //........................................         
                           for( i = 0; i < nBytes; i++ )
                           {
                              if ( 0 == *lpstTemp )
                                 *lpstTemp = 0x2C;

                              lpstTemp++;
                           }

                           // Make the changes to the bitmap.
                           //................................
                           SetDIBits( hDC, hBitmap, 0, HEIGHT, lpstBitmap,
                                      (LPBITMAPINFO) lpbi, DIB_RGB_COLORS );

                           ReleaseDC( hWnd, hDC );

                           InvalidateRect( hWnd, NULL, TRUE );
                           UpdateWindow( hWnd );
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
              GlobalFree( lpbi );
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
