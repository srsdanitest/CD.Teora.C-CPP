
#include <windows.h>  
#include "Create_Icon.h" 


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

#define EVENBYTE( i )  ((i+7)/8*8)

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static HICON hIcon;

   switch( uMsg )
   {
      case WM_CREATE :
              {
                 LPBYTE lpA, lpX;
                 LPBYTE lpAND, lpXOR;
                 int    i,j;
                 int    nWidth     = GetSystemMetrics( SM_CXICON );
                 int    nHeight    = GetSystemMetrics( SM_CYICON );
                 int    nIconBytes = (EVENBYTE(nWidth)/8)*nHeight;

                 // Allocate memory for the bit masks.
                 //...................................
                 lpA = lpAND = (LPBYTE)GlobalAlloc( GPTR, nIconBytes );
                 lpX = lpXOR = (LPBYTE)GlobalAlloc( GPTR, nIconBytes );

                 // Fill masks with icon image.
                 //............................
                 for( i=0; i < EVENBYTE( nWidth ) / 8; i++ )
                 {
                    for( j=0; j < nHeight; j++ )
                    {
                       *lpA++ = 0xFF;
                       if ( i > j )
                          *lpX++ = 0xFF;
                       else
                          *lpX++ = 0x11;
                    }
                 }

                 // Create icon.
                 //.............
                 hIcon = CreateIcon( hInst, nWidth, nHeight, 1, 1, 
                                     lpAND, lpXOR );

                 GlobalFree( lpAND );
                 GlobalFree( lpXOR );
              }
              break;
            

      case WM_PAINT  :
              {
                 PAINTSTRUCT ps;

                 BeginPaint( hWnd, &ps );
                 DrawIcon( ps.hdc, 10, 10, hIcon );
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
              DestroyIcon( hIcon );
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
