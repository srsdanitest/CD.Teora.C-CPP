
#include <windows.h>  
#include "Create_Accel.h" 


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

HACCEL hAccel = NULL;

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
      if ( !hAccel || !TranslateAccelerator( hWnd, hAccel, &msg ) )
      {
         TranslateMessage( &msg ); 
         DispatchMessage( &msg );  
      }
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


#define IDM_NEWBASE 300

VOID AddNewTestItem( HWND hWnd )
{
static int nNum = 0;

   char   szMenuItem[20];

   HMENU  hMenu      = GetMenu( hWnd );
   ACCEL* pAccelData = NULL;
   ACCEL* pCurAccel  = NULL;
   HANDLE hAccelData = NULL;
   int    nNumAccel  = 1;

   // Maximum of 4 new items allowed.
   //................................
   if ( nNum == 4 )
      return;

   // If accelerator table exists, get the number of items.
   //......................................................   
   if ( hAccel )
   {
      nNumAccel = CopyAcceleratorTable( hAccel, NULL, 0 ) + 1;
   }

   // Allocate an array of ACCEL structures.
   //.......................................
   hAccelData = GlobalAlloc( GHND, sizeof(ACCEL) * nNumAccel );
   if ( hAccelData )
      pAccelData = (ACCEL*)GlobalLock( hAccelData );

   // If an accelerator table exists, copy the items into
   // the newly allocated array.
   //....................................................
   if ( hAccel && pAccelData )
   {
      CopyAcceleratorTable( hAccel, pAccelData, nNumAccel-1 );

      DestroyAcceleratorTable( hAccel );
      hAccel = NULL;
   }

   // Add the new menu option and accelerator key
   //............................................
   if ( pAccelData )
   {
      // Get a pointer to the new accelerator key in
      // the array.
      //............................................
      pCurAccel = (ACCEL*)(pAccelData+nNumAccel-1);

      // Create a new menu option on the menu.
      //......................................
      nNum++;
      wsprintf( szMenuItem, "New Item&%d", nNum );
      AppendMenu( hMenu, MFT_STRING, IDM_NEWBASE+nNum, szMenuItem );
      DrawMenuBar( hWnd );

      // Set up a new accelerator of F1,F2,F3,or F4 for the
      // the new menu option.
      //...................................................
      pCurAccel->fVirt = FNOINVERT | FVIRTKEY;
      pCurAccel->cmd   = IDM_NEWBASE+nNum;
      pCurAccel->key   = ( nNum == 1 ? VK_F1 :
                           nNum == 2 ? VK_F2 :
                           nNum == 3 ? VK_F3 :
                           /*default*/ VK_F4 );

      // Create the new accelerator table.
      //..................................
      hAccel = CreateAcceleratorTable( pAccelData, nNumAccel );

      GlobalUnlock( hAccelData );
   }

   if ( hAccelData )
      GlobalFree( hAccelData );
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch( uMsg )
   {
      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                         AddNewTestItem( hWnd );
                         break;

                 case IDM_NEWBASE+1 :
                         MessageBox( hWnd, "New Item 1 Selected", "Item Selected", 
                                     MB_OK | MB_ICONINFORMATION );
                         break;

                 case IDM_NEWBASE+2 :
                         MessageBox( hWnd, "New Item 2 Selected", "Item Selected", 
                                     MB_OK | MB_ICONINFORMATION );
                         break;

                 case IDM_NEWBASE+3 :
                         MessageBox( hWnd, "New Item 3 Selected", "Item Selected", 
                                     MB_OK | MB_ICONINFORMATION );
                         break;

                 case IDM_NEWBASE+4 :
                         MessageBox( hWnd, "New Item 4 Selected", "Item Selected", 
                                     MB_OK | MB_ICONINFORMATION );
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
