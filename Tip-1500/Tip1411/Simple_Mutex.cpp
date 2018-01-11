#include <genstub.cpp>

//  Child thread procedure waits until mutex becomes signaled, holds the
// object for five seconds and then releases it.

DWORD WINAPI ChildThreadProc( HWND hWnd )
{
    char szBuffer[128];
    HANDLE hMutex = OpenMutex( MUTEX_ALL_ACCESS, FALSE, "EXAMPLE_MUTEX" );
    wsprintf( szBuffer,"Thread %x waiting for Mutex",
                 GetCurrentThreadId( ));
    SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
    // Wait for signaled mutex.
    WaitForSingleObject( hMutex, INFINITE );
    wsprintf( szBuffer,"Thread %x got mutex!", GetCurrentThreadId( ) );
    SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
    Sleep( 5000 ); // Shut out other threads.
    // Release mutex.
    wsprintf( szBuffer,"Thread %x is done with mutex", GetCurrentThreadId( ) );
    SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
    ReleaseMutex( hMutex );
    CloseHandle( hMutex );
    ExitThread( TRUE );
}

// Windows message procedure.
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   static HANDLE hMutex = 0;

   switch (uMsg) {
           case WM_CREATE:
                   hMutex = CreateMutex( NULL, FALSE, "EXAMPLE_MUTEX" );
                   return DefWindowProc( hWnd, uMsg, wParam, lParam );
           case WM_COMMAND:       // process menu items
                   switch ( LOWORD( wParam )  )
                   {
                      case IDM_TEST: // Make a thread
                        {
                           DWORD id;
                           CreateThread( NULL, 0, ChildThreadProc, hWnd, 0, &id );
                        }
                      break;
                      case IDM_EXIT:
                           DestroyWindow( hWnd );
                           break;
                   }
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
                      if ( row > 200 )
                         row = 0;
                      else
                         row += 20;
                      ReleaseDC( hWnd, hDC );
                   }
                   break;
           case WM_DESTROY:
                   if ( hMutex )
                      CloseHandle( hMutex );
                   PostQuitMessage( 0 );
                   break;
           default:
                return DefWindowProc( hWnd, uMsg, wParam, lParam );
   }
   return NULL;
}