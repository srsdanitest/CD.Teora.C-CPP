#include <genstub.cpp>

CRITICAL_SECTION cs;

// Child thread procedure.
DWORD WINAPI ChildThreadProc(HWND hWnd)
{
   TCHAR szBuffer[256];    // Work area for print formatting.
   wsprintf( szBuffer, "Thread %x waiting for critical section", GetCurrentThreadId() );
   SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
   // Enter protected code.
   EnterCriticalSection( &cs );
   wsprintf( szBuffer,"Thread %x in critical section", GetCurrentThreadId() );
   SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
   Sleep( 5000 );  // This is where our critical code would go if we had some.
   // All done now, let someone else in.
   LeaveCriticalSection( &cs );
   wsprintf( szBuffer,"Thread %x has exited critical section", GetCurrentThreadId() );
   SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
   ExitThread(TRUE);
}

// Main Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
           case WM_CREATE:  // A critical section must be initialized before it is used.
                   InitializeCriticalSection(&cs);
                   return DefWindowProc( hWnd, uMsg, wParam, lParam );
           case WM_COMMAND:       // Process menu items.
                   switch ( LOWORD( wParam ) )
                   {
                        case IDM_TEST:
                        {
                           DWORD dwChildID;
                           CreateThread( NULL, 0, ChildThreadProc, hWnd, 0, &dwChildID );
                        }
                        break;
                        case IDM_EXIT:
                           DestroyWindow( hWnd );
                           break;
                   }
           break;
           case WM_USER:
                   {  // Show synchronization activity.
                      TCHAR szBuffer[101];
                      static int row = 0;
                      static int msg_num = 1;
                      HDC hDC = GetDC( hWnd );
                      FillMemory( szBuffer, 100, 32 );
                      TextOut( hDC, 0, row, szBuffer, 100 );
                      wsprintf( szBuffer, "%3d: %s", msg_num++, (LPTSTR)lParam );
                      TextOut( hDC, 0, row, szBuffer, lstrlen( szBuffer ) );
                      if ( row > 200 )
                         row = 0;
                      else
                         row += 20;
                      ReleaseDC( hWnd, hDC );
                   }
                   break;
           case WM_DESTROY: // Get back resources from critical section object.
                   DeleteCriticalSection(&cs);
                   PostQuitMessage( 0 );
                   break;
           default:
                return DefWindowProc( hWnd, uMsg, wParam, lParam );
   }
   return NULL;
}