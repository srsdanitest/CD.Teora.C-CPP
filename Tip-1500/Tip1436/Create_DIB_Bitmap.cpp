
#include <windows.h>  
#include "Create_DIB_Bitmap.h" 


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
   switch( uMsg )
   {
      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        {
                           BITMAPINFOHEADER  bi;
                           BITMAPINFOHEADER* lpbi;
                           HBITMAP           hBitmap;
                           HDC               hDC, hMemDC;
                           HANDLE            hDIB;

                           // Initialize the BITMAPINFOHEADER structure.
                           //...........................................
                           bi.biSize     = sizeof( BITMAPINFOHEADER );
                           bi.biWidth    = 50;
                           bi.biHeight   = 50;
                           bi.biPlanes   = 1;
                           bi.biBitCount = 4;
                           bi.biCompression   = BI_RGB;
                           bi.biSizeImage     = 0;
                           bi.biXPelsPerMeter = 0;
                           bi.biYPelsPerMeter = 0;
                           bi.biClrUsed       = 0;
                           bi.biClrImportant  = 0;

                           hDC = GetDC( hWnd );

                           // Create DIB.
                           //............
                           hBitmap = CreateDIBitmap( hDC, &bi, 0L, NULL, 
                                                     NULL, 0 );

                           // Allocate memory for BITMAPINFO structure.
                           //..........................................
                           hDIB    = GlobalAlloc( GHND, 
                                                  sizeof( BITMAPINFOHEADER )+
                                                  16 * sizeof( RGBQUAD ) );

                           lpbi = (BITMAPINFOHEADER*)GlobalLock( hDIB );

                           // Copy bi to top of BITMAPINFO structure.
                           //........................................
                           *lpbi = bi;

                           // Use GetDIBits() to init bi struct data.
                           //........................................
                           GetDIBits( hDC, hBitmap, 0, 50, NULL, 
                                      (LPBITMAPINFO)lpbi, DIB_RGB_COLORS );
                           GlobalUnlock( hDIB );

                           // Create a memory device context 
                           // and select the DIB into it.
                           //...............................
                           hMemDC = CreateCompatibleDC( hDC );
                           SelectObject( hMemDC, hBitmap );

                           // Paint on memory device context.
                           //................................
                           SelectObject( hMemDC, GetStockObject(BLACK_BRUSH));
                           Rectangle( hMemDC, 0, 0, 50, 50 );

                           SelectObject( hMemDC, GetStockObject(WHITE_BRUSH));
                           Ellipse( hMemDC, 0, 0, 50, 50 );
                           Ellipse( hMemDC, 10, 0, 40, 50 );
                           Ellipse( hMemDC, 20, 0, 30, 50 );

                           // Paint the bitmap on the display.
                           //.................................
                           BitBlt( hDC, 0, 0, 50, 50,
                                   hMemDC, 0, 0, SRCCOPY );

                           DeleteDC( hMemDC );
                           GlobalFree( hDIB );
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
