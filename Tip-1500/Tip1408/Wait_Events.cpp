#include <genstub.cpp>

// Child thread procedure. The child waits to get event. It then sits idle
// for five seconds and sets the event again so another thread can use it.
DWORD WINAPI ChildThreadProc( HWND hWnd )
{
   char szBuffer[256];         // work area for print formatting
   HANDLE hAutoEvent = OpenEvent( SYNCHRONIZE, FALSE, "EXAMPLE-AUTOEVENT");
   wsprintf( szBuffer, "Thread %x waiting for Event %x",
            GetCurrentThreadId(  ), hAutoEvent );
   SendMessage( hWnd, WM_USER, 0, (LPARAM)szBuffer );
   // Check that write auto reset is signaled.
   WaitForSingleObject( hAutoEvent, INFINITE );
   wsprintf( szBuffer,"Thread %x got event", GetCurrentThreadId( ) );
   SendMessage( hWnd, WM_USER, 0, (LPARAM)szBuffer );
   Sleep( 5000 );
   // Release event.
   wsprintf( szBuffer,"Thread %x is done with event", GetCurrentThreadId( ) );
   SendMessage( hWnd, WM_USER, 0, (LPARAM)szBuffer );
   SetEvent( hAutoEvent );
   CloseHandle( hAutoEvent );
   ExitThread( TRUE );
}

// Windows message procedure.
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   static HANDLE hAutoEvent = 0;

   switch (uMsg)
   {
           case WM_CREATE: // Make an auto-reset event with initial state of signaled.
                   hAutoEvent = CreateEvent( NULL, FALSE, TRUE, "EXAMPLE-AUTOEVENT");
                   return DefWindowProc( hWnd, uMsg, wParam, lParam );
           case WM_DESTROY:
                   if ( hAutoEvent )
                      CloseHandle( hAutoEvent );
                   PostQuitMessage( 0 );
                   break;
           case WM_USER:
                   {  // Message to show synchronization actions.
                      TCHAR szBuffer[101];
                      static int row = 0;
                      static int msg_num = 1;
                      HDC hDC = GetDC( hWnd );

                      FillMemory( szBuffer, 100, 32 );
                      TextOut( hDC, 0, row, szBuffer, 100 );
                      wsprintf( szBuffer, "%3d: %s", msg_num++, (LPTSTR)lParam );
                      TextOut( hDC, 0, row, szBuffer, lstrlen( szBuffer ) );
                      row = ( row > 200 ) ? 0 : row+=20;
                      ReleaseDC( hWnd, hDC );
                   }
                   break;
           case WM_COMMAND:       // process menu items
                   switch ( LOWORD( wParam )  )
                   {
                      case IDM_TEST:
                      {
                           DWORD id = 0;
                           CreateThread( NULL, 0, ChildThreadProc, hWnd, 0, &id );
                      }
                      break;
                      case IDM_EXIT:
                           DestroyWindow( hWnd );
                      break;
                   }
           break;
           default:
                return DefWindowProc( hWnd, uMsg, wParam, lParam );
   }
   return NULL;
}