#include <genstub.cpp>

// Define these menu options in a popup menu.
#define IDM_WORST    401
#define IDM_LOW      402
#define IDM_NORMAL   403
#define IDM_HIGH     404
#define IDM_BEST     405

//  Function that wastes CPU time.
DWORD GoWasteSomeCPU(void)
{
    long i, j;
    DWORD dwTicksNow = GetTickCount( );
    for ( i = 0; i < 100000; i ++ )
        for ( j = 0; j < 1000; j ++ );
    return GetTickCount( ) - dwTicksNow;
}

// Windows Message Procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
            case WM_COMMAND:       // process menu items
                {
                    HANDLE hThread = GetCurrentThread();
                    switch ( LOWORD( wParam ) )
                    {
                        case IDM_WORST:
                            SetThreadPriority( hThread, THREAD_PRIORITY_LOWEST );
                            SendMessage( hWnd, WM_USER, 0, GoWasteSomeCPU() );
                            break;
                        case IDM_LOW:
                            SetThreadPriority( hThread, THREAD_PRIORITY_BELOW_NORMAL );
                            SendMessage( hWnd, WM_USER, 0, GoWasteSomeCPU() );
                            break;
                        case IDM_NORMAL:
                            SetThreadPriority( hThread, THREAD_PRIORITY_NORMAL );
                            SendMessage( hWnd, WM_USER, 0, GoWasteSomeCPU() );
                            break;
                        case IDM_HIGH:
                            SetThreadPriority( hThread, THREAD_PRIORITY_ABOVE_NORMAL );
                            SendMessage( hWnd, WM_USER, 0, GoWasteSomeCPU() );
                            break;
                        case IDM_BEST:
                            SetThreadPriority( hThread, THREAD_PRIORITY_HIGHEST );
                            SendMessage( hWnd, WM_USER, 0, GoWasteSomeCPU() );
                            break;
                        case IDM_EXIT:
                            DestroyWindow(hWnd);
                        break;
                    }
                }
                break;
            case WM_USER:
                {
                    TCHAR szBuffer[128];
                    static int nRow = 0;
                    HDC hDC = GetDC( hWnd );
                    wsprintf( szBuffer, "Priority for Thread %lX is %d. Test Speed = %d ",
                              GetCurrentThreadId( ), GetThreadPriority( GetCurrentThread( ) ),
                              lParam );
                    TextOut( hDC, 0, nRow, szBuffer, lstrlen( szBuffer ) );
                    ReleaseDC( hWnd, hDC );
                    nRow += 20;
                    if (nRow > 220)
                       nRow = 0;
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