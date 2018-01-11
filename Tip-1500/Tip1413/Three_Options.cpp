#include <genstub.cpp>

// Add these menu options.
#define IDM_READ    201
#define IDM_WRITE   202

// Windows message procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hSemRead = 0;         // Handle of the read semaphore.
    static HANDLE hEventWrite = 0;      // Handle of the write event.
    switch (uMsg)
    {
            case WM_CREATE: // Make the two synchornization objects.
                    {
                       hSemRead = CreateSemaphore( NULL, 10, 10 "READ SEMAPHORE" );
                       hEventWrite = CreateEvent( NULL, TRUE, TRUE, "WRITE EVENT" );
                       return DefWindowProc( hWnd, uMsg, wParam, lParam );
                    }
                    break;
            case WM_DESTROY: // Close the synchonization objects.
                    if ( hSemRead )
                       CloseHandle( hSemRead );
                    if ( hEventWrite )
                       CloseHandle( hEventWrite );
                    PostQuitMessage( 0 );
                    break;
            case WM_COMMAND:       // Process menu items
                    switch ( LOWORD( wParam )  )
                    {
                       case IDM_READ:
                            hSemRead = OpenSemaphore( SEMAPHORE_ALL_ACCESS, FALSE,
                                                      "Read Semaphore" );
                            hEventWrite = OpenEvent( SYNCHRONIZE, FALSE, "Write Event" );
                            SetWindowText( hWnd, "Waiting for all Writes to Finish" );
                            // Check that write manual reset event is signaled.
                            WaitForSingleObject( hEventWrite, INFINITE );
                            // Wait for semaphore.
                            WaitForSingleObject( hSemRead, INFINITE );
                            // Do the read.
                            SetWindowText( hWnd, "Reading" );
                            Sleep( 5000 );    // Sleep instead to dramatize contention.
                            // Release semaphore.
                            ReleaseSemaphore( hSemRead, 1, NULL );
                            SetWindowText( hWnd, "Done Reading" );
                            CloseHandle( hSemRead );
                            CloseHandle( hEventWrite );
                        break;
                        case IDM_WRITE:
                        {
                            DWORD dwSemaphoreCount = 0;
                            hSemRead = OpenSemaphore( SEMAPHORE_ALL_ACCESS, FALSE,
                                                      "Read Semaphore" );
                            hEventWrite = OpenEvent( SYNCHRONIZE, FALSE, "Write Event" );
                            // Wait for manual reset event object: it becomes non-signaled.
                            SetWindowText( hWnd, "Waiting for Write Event" );
                            WaitForSingleObject( hEventWrite, INFINITE );
                            ResetEvent( hEventWrite );
                            SetWindowText( hWnd, "Waiting for All Reads to Finish" );
                            // Get semaphore, Release semaphore until its count is maximum.
                            while ( dwSemaphoreCount!=SEMAPHORE_MAX_COUNT )
                            {
                                WaitForSingleObject( hSemRead, INFINITE );
                                ReleaseSemaphore( hSemRead, 1, &dwSemaphoreCount );
                                dwSemaphoreCount++;
                            }
                            SetWindowText( hWnd, "Writing" );
                            // Do the write.
                            Sleep( 10000 );  // Sleep instead to dramatize contention.
                            SetWindowText( hWnd, "Done Writing" );
                            // SetEvent: it becomes signaled.
                            SetEvent( hEventWrite );
                            CloseHandle( hSemRead );
                            CloseHandle( hEventWrite );
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