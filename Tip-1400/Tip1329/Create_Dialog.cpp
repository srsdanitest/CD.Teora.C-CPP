
#include <windows.h>  
#include "CreateDialog.h" 


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

HWND hDlgModeless = NULL;
BOOL bChecked     = FALSE;
BOOL bRadio1      = TRUE;

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
      if ( hDlgModeless || !IsDialogMessage( hDlgModeless, &msg ) )
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


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch( uMsg )
   {
      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        if ( !hDlgModeless )
                           hDlgModeless = CreateDialog( hInst, "TestDialog", 
                                                hWnd, (DLGPROC)TestDlgProc );
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


LRESULT CALLBACK TestDlgProc( HWND hDlg, UINT uMsg, 
                              WPARAM wParam, LPARAM lParam )
{
   switch( uMsg )
   {
      // Initially set the check box
      // and radio button states.
      //............................
      case WM_INITDIALOG :
            CheckDlgButton( hDlg, IDC_CHECKBOX, bChecked ? MF_CHECKED :
                                                           MF_UNCHECKED );
            CheckRadioButton( hDlg, IDC_RADIO1, IDC_RADIO2, 
                           bRadio1 ? IDC_RADIO1 : IDC_RADIO2 );
            break;

      case WM_COMMAND :
            switch( LOWORD( wParam ) )
            {
               case IDC_CHECKBOX :
                      bChecked = !IsDlgButtonChecked( hDlg, IDC_CHECKBOX );
                      CheckDlgButton( hDlg, IDC_CHECKBOX, 
                                      bChecked ? MF_CHECKED : MF_UNCHECKED );
                      break;

               case IDC_RADIO1 :
                      bRadio1 = TRUE;
                      CheckRadioButton( hDlg, IDC_RADIO1, IDC_RADIO2,
                                                          IDC_RADIO1 );
                      break;

               case IDC_RADIO2 :
                      bRadio1 = FALSE;
                      CheckRadioButton( hDlg, IDC_RADIO1, IDC_RADIO2,
                                                          IDC_RADIO2 );
                      break;

               case IDCANCEL : 
                      DestroyWindow( hDlg ); 
                      break;
            }
            break;

       case WM_DESTROY :
            hDlgModeless = NULL;
            break;

      default :
            return( FALSE );
   }

   return( TRUE );
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
