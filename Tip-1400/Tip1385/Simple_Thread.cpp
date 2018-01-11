#include <genstub.cpp>

// This is a child thread procedure that waits for a semaphore,
// holds the semaphore for five seconds, and releases the semaphore.
// Threads that cannot get semaphores will wait until other threads exit.
DWORD WINAPI ChildThreadProc( HWND hWnd )
{
    TCHAR szBuffer[256];                            // buffer
    DWORD dwSemCount = 0;                           // printing semaphore count
    HANDLE hSemaphore = OpenSemaphore( SYNCHRONIZE, FALSE, "TEST_SEMAPHORE" );
    wsprintf( szBuffer,"Thread %x waiting for semaphore %x",
             GetCurrentThreadId( ), hSemaphore );
    SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
    // Check for signaled semaphore.
    WaitForSingleObject( hSemaphore, INFINITE );
    wsprintf( szBuffer,"Thread %x got semaphore", GetCurrentThreadId( ) );
    SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
    Sleep( 5000 );
    // Release semaphore.
    ReleaseSemaphore( hSemaphore, 1, &dwSemCount );
    wsprintf( szBuffer,"Thread %x is done with semaphore. Its count was %ld.",
            GetCurrentThreadId( ), dwSemCount );
    SendMessage( hWnd, WM_USER, 0, (LPARAM) szBuffer );
    CloseHandle( hSemaphore );
    ExitThread( TRUE );
}

// Windows message procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   static HANDLE hSemaphore = 0;

   switch (uMsg)
   {
           case WM_CREATE:
                   hSemaphore = CreateSemaphore( NULL, 4, 4, "TEST_SEMAPHORE" );
                   return DefWindowProc( hWnd, uMsg, wParam, lParam );
           case WM_COMMAND:       // process menu items
                   switch ( LOWORD( wParam )  )
                   {
                      case IDM_TEST:     // start up a thread.
                        {
                           DWORD dwChildId;
                           CreateThread( NULL, 0, ChildThreadProc, hWnd, 0, &dwChildId );
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
                   if ( hSemaphore )
                      CloseHandle( hSemaphore );
                   PostQuitMessage( 0 );
                   break;
           default:
                return DefWindowProc( hWnd, uMsg, wParam, lParam );
   }
   return NULL;
}