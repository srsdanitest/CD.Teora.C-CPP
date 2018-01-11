
#include <windows.h>  
#include "Draw_2_Boxes.h" 


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
static HPALETTE hPalette;
static int      nColorData;

   switch( uMsg )
   {
      case WM_CREATE  :
              {
                 HANDLE       hRes, hPal;
                 LPBITMAPINFO lpBi;
                 LPLOGPALETTE lpPal;
                 int          i;

                 // Load the bitmap.
                 //.................
                 hRes = LoadResource( hInst, 
                            FindResource( hInst, "testdib", RT_BITMAP ) );

                 lpBi = (LPBITMAPINFO)LockResource( hRes );

                 // Find out how many colors we need.
                 //..................................
                 if ( lpBi->bmiHeader.biClrUsed != 0 )
                    nColorData = lpBi->bmiHeader.biClrUsed;
                 else
                    switch( lpBi->bmiHeader.biBitCount )
                    {
                       case 1  : nColorData = 2;   break; // Monochrome
                       case 4  : nColorData = 16;  break; // VGA
                       case 8  : nColorData = 256; break; // SVGA
                       case 24 : nColorData = 0;   break; // True Color
                    }

                 // Allocate memory for color palette.
                 //...................................
                 hPal = GlobalAlloc( GHND, sizeof(LOGPALETTE)+
                                        (nColorData * sizeof(PALETTEENTRY)) );
                 lpPal = (LPLOGPALETTE)GlobalLock( hPal );

                 lpPal->palVersion    = 0x300;      
                 lpPal->palNumEntries = nColorData;

                 // Load each color into the palette.
                 //..................................
                 for ( i = 0; i < nColorData; i++ )
                 {
                    lpPal->palPalEntry[i].peRed   = lpBi->bmiColors[i].rgbRed;
                    lpPal->palPalEntry[i].peGreen = 
                                                  lpBi->bmiColors[i].rgbGreen;
                    lpPal->palPalEntry[i].peBlue  = 
                                                  lpBi->bmiColors[i].rgbBlue;
                 }

                 // Create the Palette.
                 //....................
                 hPalette = CreatePalette( lpPal );

                 GlobalUnlock( hPal );
                 GlobalFree( hPal );
              }
              break;

      case WM_PAINT :
              {
                 PAINTSTRUCT  ps;
                 LPBITMAPINFO lpBi;
                 HANDLE       hRes;
                 LPTSTR       lpBits;

                 BeginPaint( hWnd, &ps );

                 // Select palette and realize it.
                 //...............................
                 SelectPalette( ps.hdc, hPalette, FALSE );
                 RealizePalette( ps.hdc );

                 // Load the bitmap.
                 //.................
                 hRes = LoadResource( hInst, 
                            FindResource( hInst, "testdib", RT_BITMAP ) );

                 lpBi = (LPBITMAPINFO)LockResource( hRes );

                 // Locate the bitmap data.
                 //........................
                 lpBits =  (LPSTR) lpBi;
                 lpBits +=  lpBi->bmiHeader.biSize + 
                            ( nColorData*sizeof(RGBQUAD) );

                 // Paint the bitmap normal size.
                 //..............................
                 SetDIBitsToDevice( ps.hdc, 10, 10, 
                                            lpBi->bmiHeader.biWidth,
                                            lpBi->bmiHeader.biHeight,
                                            0, 0,
                                            0, lpBi->bmiHeader.biHeight,
                                            lpBits, lpBi, DIB_RGB_COLORS );

                 // Paint the bitmap 200% size.
                 //............................
                 StretchDIBits( ps.hdc, 40+lpBi->bmiHeader.biWidth, 10,
                                        lpBi->bmiHeader.biWidth*2,
                                        lpBi->bmiHeader.biHeight*2,
                                        0, 0,
                                        lpBi->bmiHeader.biWidth,
                                        lpBi->bmiHeader.biHeight,
                                        lpBits, lpBi, DIB_RGB_COLORS, 
                                        SRCCOPY );

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
              DeleteObject( hPalette );
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
