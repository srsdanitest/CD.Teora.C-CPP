#include <genstub.c>

#define OUR_ERROR 0x10000000

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   static UINT uClicks;
   static UINT uRow;
   switch (uMsg)
   {
         case WM_CREATE:
               uRow = 0;
               uClicks = 0;
               return DefWindowProc( hWnd, uMsg, wParam, lParam);
         case WM_DESTROY:
               PostQuitMessage( 0 );
               break;
         case WM_COMMAND:
               switch ( LOWORD( wParam ) )
               {
                     case IDM_TEST:
                     {
                           HANDLE hModule;
                           char szBuffer[128];
                           HDC hDC = GetDC(hWnd);
                           // Turn off the DLL not found error mode.
                           UINT uOldMode = SetErrorMode( SEM_NOOPENFILEERRORBOX );
                           if ( (hModule = LoadLibrary("GetLast.DLL")) )
                           {
                              // Get address of external function.
                              FARPROC lpfnSetErrorCondition;
                              lpfnSetErrorCondition =
                                    GetProcAddress(hModule, "SetTheErrorCondition");
                              // Call external function to change error code.
                              if (lpfnSetErrorCondition)
                                 (*lpfnSetErrorCondition) (OUR_ERROR + uClicks++);
                           }
                           TextOut( hDC, 0, 16 * uRow++, szBuffer,
                                    wsprintf(szBuffer,"Error code is: %X",
                                    GetLastError() ));
                           SetErrorMode( uOldMode );
                           ReleaseDC(hWnd, hDC);
                     }
                     break;
                     case IDM_EXIT:
                           DestroyWindow( hWnd );
                           break;
               }
               break;
         default:
               return (DefWindowProc(hWnd, uMsg, wParam, lParam));
   }
   return (NULL);
}
