#include <windows.h>
#include "tst_max.h"
#if defined (win32)
   #define IS_WIN32 TRUE
#else
   #define IS_WIN32 FALSE
#endif

HINSTANCE hInst;        // current instance
LPCTSTR lpszAppName = "Generic";
LPCTSTR lpszTitle =   "Generic Application";
BOOL RegisterWin95(CONST WNDCLASS* lpwc);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
   MSG msg;
   HWND hWnd;
   WNDCLASS wc;

   wc.style          = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc    = (WNDPROC)WndProc;
   wc.cbClsExtra     = 0;
   wc.cbWndExtra     = 0;
   wc.hInstance      = 0;
   wc.hIcon          = LoadIcon(hInstance, lpszAppName);
   wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
   wc.lpszMenuName   = lpszAppName;
   wc.lpszClassName  = lpszAppName;

   if(!RegisterWin95(&wc))
      return false;
   hInst = hInstance;
   hWnd = CreateWindow (lpszAppName,
                        lpszTitle,
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, 0,
                        CW_USEDEFAULT, 0,
                        NULL,
                        NULL,
                        hInstance,
                        NULL
                       );
   if(!hWnd)
      return false;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   while(GetMessage(&msg, NULL, 0,0))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
   return(msg.wParam);
 }

BOOL RegisterWin95(CONST WNDCLASS* lpwc)
 {
   WNDCLASSEX wcex;

   wcex.style           = lpwc->style;
   wcex.lpfnWndProc     = lpwc->lpfnWndProc;
   wcex.cbClsExtra      = lpwc->cbClsExtra;
   wcex.cbWndExtra      = lpwc->cbWndExtra;
   wcex.hInstance       = lpwc->hInstance;
   wcex.hIcon           = lpwc->hIcon;
   wcex.hCursor         = lpwc->hCursor;
   wcex.hbrBackground   = lpwc->hbrBackground;
   wcex.lpszMenuName    = lpwc->lpszMenuName;
   wcex.lpszClassName   = lpwc->lpszClassName;
   wcex.cbSize          = sizeof(WNDCLASSEX);
   wcex.hIconSm         = LoadIcon(wcex.hInstance, "SMALL");
   return RegisterClassEx(&wcex);
 }

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 {
   switch(uMsg)
    {
      case WM_COMMAND:
         switch(LOWORD(wParam))
          {
            case IDM_TEST :
               ShowWindow(hWnd, SW_SHOWMAXIMIZED);
               break;
            case IDM_EXIT :
               DestroyWindow(hWnd);
               break;
          }
         break;
      case WM_DESTROY :
         PostQuitMessage(0);
         break;
      default:
         return (DefWindowProc(hWnd, uMsg, wParam, lParam));
    }
   return(0L);
 }

