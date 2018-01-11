#include <genstub.c>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
         case WM_CREATE:  // Set current directory to value passed on command line.
         {
               char   szMessage[MAX_PATH + 31];
               char   szCommandLine[MAX_PATH + 1];
               LPTSTR lpToken = NULL;
               LPTSTR lpszDirName = NULL;
               DWORD  dwcCurDir = MAX_PATH;

               lstrcpy( szCommandLine, GetCommandLine() );
               // Search for extra input after program name.
               if ( ( lpToken = strstr( szCommandLine, " " ) ) )
               {
                  // Get first argument by itself, if there is one.
                  lpszDirName = strtok( lpToken, " " );
                  if ( lpszDirName )
                  {
                     // Use lpTemp pointer to isolate 1st arg.
                     LPTSTR lpTemp = strstr(lpszDirName, " ");
                     if (lpTemp)
                        *lpTemp = 0;
                     // Attempt to change the current directory.
                     if ( !SetCurrentDirectory(lpszDirName) )
                        wsprintf( szMessage,
                                  "Cannot set current directory to [%s]",
                                  lpszDirName );
                     else
                        wsprintf( szMessage, "Set current directory to [%s]",
                                  lpszDirName );
                     // Report result of operation.
                     MessageBox( hWnd, szMessage,
                                 "Result of SetCurrentDirectory()", MB_OK );
                  }
               }
         }
         return DefWindowProc( hWnd, uMsg, wParam, lParam );

         case WM_COMMAND:
               switch ( LOWORD( wParam ) )
               {
                     case IDM_TEST:
                     {
                           char szBuffer[MAX_PATH + 1];
                           DWORD dwcNameSize = MAX_PATH + 1;

                           // Now query the system for the paths.
                           GetCurrentDirectory( dwcNameSize, &szBuffer );
                           MessageBox( hWnd, szBuffer, "Current Directory", MB_OK );
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