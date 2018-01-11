#include <genstub.cpp>

// Hot key values.
#define RESUME_KEY    101
#define SUSPEND_KEY   102
#define TERMINATE_KEY 103

DWORD WINAPI ThreadProc(HWND hWnd)
{
    TCHAR szBuffer[128];
    wsprintf( szBuffer, "Starting Thread ID = %lX", GetCurrentThreadId() );
    SetWindowText( hWnd, szBuffer );
    Sleep( 5000 );
    wsprintf( szBuffer, "Thread %lX finished execution", GetCurrentThreadId() );
    SetWindowText( hWnd, szBuffer );
    ExitThread( TRUE );
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static  HANDLE hChild = 0;

    switch (uMsg)
    {
            case WM_CREATE:
                    RegisterHotKey(hWnd, RESUME_KEY, MOD_ALT, 'R');
                    RegisterHotKey(hWnd, SUSPEND_KEY, MOD_ALT, 'S');
                    RegisterHotKey(hWnd, TERMINATE_KEY, MOD_ALT, 'K');
                    return DefWindowProc( hWnd, uMsg, wParam, lParam );
            case WM_DESTROY:
                    UnregisterHotKey(hWnd, RESUME_KEY);
                    UnregisterHotKey(hWnd, SUSPEND_KEY);
                    UnregisterHotKey(hWnd, TERMINATE_KEY);
                    PostQuitMessage( 0 );
                    break;
            case WM_HOTKEY:
                    {
                       TCHAR szBuffer[128];
                       DWORD dwExitCodeThread = STILL_ACTIVE;
                       lstrcpy( szBuffer, "No Child Thread Running" );
                       if (hChild)
                          GetExitCodeThread(hChild, &dwExitCodeThread);
                       if (dwExitCodeThread==STILL_ACTIVE)
                          switch (wParam)
                          {
                             case SUSPEND_KEY:
                                 wsprintf( szBuffer, "Suspending thread %lX", hChild );
                                 SuspendThread(hChild);
                                 break;
                             case RESUME_KEY:
                                 wsprintf( szBuffer, "Resuming thread %lX", hChild );
                                 ResumeThread(hChild);
                                 break;
                             case TERMINATE_KEY:
                                 wsprintf( szBuffer, "Terminating thread %lX", hChild );
                                 TerminateThread(hChild, FALSE);
                                 break;
                          }
                       SetWindowText( hWnd, szBuffer );
                    }
                    break;
            case WM_COMMAND:  // Process menu items.
                    switch ( LOWORD( wParam )  )
                    {
                        case IDM_TEST:
                           {  // Start a thread. Only one thread at at time.
                              DWORD dwExitCodeThread;
                              DWORD dwChild;
                              if (hChild)
                                 GetExitCodeThread( hChild, &dwExitCodeThread );
                              if (dwExitCodeThread!=STILL_ACTIVE)
                                 hChild = CreateThread(NULL, 0, ThreadProc, hWnd, 0, &dwChild );
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