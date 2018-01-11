#include <genstub.cpp>

// Windows message procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
            case WM_COMMAND:       /* process menu items */
                    switch ( LOWORD( wParam )  )
                    {
                        case IDM_TEST:  // force a paint to display screen.
                        {
                            TCHAR szBuffer[128];
                            // Show the desktop.
                            HDESK hDesktopObject = GetThreadDesktop( GetCurrentThreadId( ) );
                            wsprintf( szBuffer, "Desktop Object is %x", hDesktopObject );
                            MessageBox( hWnd, szBuffer, "GetThreadDesktop()", MB_OK );
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