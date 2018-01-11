#include <genstub.cpp>

// Child thread procedure just displays a message box with information.
DWORD WINAPI ChildThreadProc(HWND hWnd)
{
    TCHAR szBuffer[256];
    wsprintf(szBuffer,
             "Process Handle = %x, ID = %x, Thread: Handle = %x, ID = %x",
             GetCurrentProcess(), GetCurrentProcessId(),
             GetCurrentThread(), GetCurrentThreadId());
    MessageBox( hWnd, szBuffer, "Process/Thread Report", MB_OK );
    ExitThread(TRUE);
}

// Main Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
         case WM_COMMAND:       // Process menu items.
               switch ( LOWORD( wParam )  )
               {
                  case IDM_TEST:
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
         case WM_DESTROY:
               PostQuitMessage( 0 );
               break;
         default:
               return DefWindowProc( hWnd, uMsg, wParam, lParam );
   }
   return NULL;
}