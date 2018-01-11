#include <genstub.c>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
         case WM_COMMAND:
               switch ( LOWORD( wParam ) )
               {
                     case IDM_TEST:
                     {
                           char szBuffer[MAX_PATH + 21];
                           DWORD dwcNameSize = MAX_PATH + 1;
                           HDC hDC = GetDC( hWnd );

                           lstrcpy( szBuffer, "Windows Directory: " );
                           GetWindowsDirectory( &szBuffer[19], (UINT) dwcNameSize );
                           TextOut( hDC, 0, 20, szBuffer, strlen( szBuffer ) );
                           lstrcpy( szBuffer, "System Directory: " );
                           GetSystemDirectory( &szBuffer[18], (UINT) dwcNameSize );
                           TextOut( hDC, 0, 40, szBuffer, strlen( szBuffer ) );

                           ReleaseDC( hWnd, hDC );
                     }
                     break;
                     case IDM_EXIT:
                           DestroyWindow( hWnd );
                           break;
               }
               break;
         case WM_DESTROY:
               PostQuitMessage( 0 );
               break;
         default:
               return (DefWindowProc(hWnd, uMsg, wParam, lParam));
   }
   return (NULL);
}