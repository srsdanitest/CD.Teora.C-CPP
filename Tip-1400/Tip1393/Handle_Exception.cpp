#include <genstub.cpp>

#define OUR_EXCEPTION  0xE0000001

LONG WINAPI OurUnhandledExceptionFilter(LPEXCEPTION_POINTERS lpExceptionData)
{
   EXCEPTION_RECORD *ExceptionRecord = lpExceptionData->ExceptionRecord;
   CONTEXT *ContextRecord = lpExceptionData->ContextRecord;
   if (ExceptionRecord->ExceptionCode==OUR_EXCEPTION)
   {
      MessageBox( NULL, "Trapped raised exception", "Unhandled Exception Filter", MB_OK );
      return EXCEPTION_EXECUTE_HANDLER;
   }
   else
      return EXCEPTION_CONTINUE_SEARCH;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
      case WM_COMMAND:
         switch ( LOWORD( wParam )  )
         {
            case IDM_TEST:
            {
               char szBuffer[128];
               HDC hDC = GetDC( hWnd );
               // Set unhandled exception handler.
               SetUnhandledExceptionFilter(OurUnhandledExceptionFilter);
               // Raise exception try block.
               try
               {
                  wsprintf( szBuffer, "Raising OUR_EXCEPTION first time" );
                  MessageBox( hWnd, szBuffer, "Try Block", MB_OK );
                  RaiseException(OUR_EXCEPTION, 0, 0, NULL);
               }
               except( GetExceptionCode() == OUR_EXCEPTION )
               {
                  wsprintf( szBuffer, "Trapped OUR_EXCEPTION in normal filter" );
                  MessageBox( hWnd, szBuffer, "Except Block", MB_OK );
               }
               // Raise exception again using unhandled exception filter.
               try
               {
                  wsprintf( szBuffer, "Raising OUR_EXCEPTION second time" );
                  MessageBox( hWnd, szBuffer, "Try Block", MB_OK );
                  RaiseException(OUR_EXCEPTION, 0, 0, NULL);
               }
               except (UnhandledExceptionFilter(GetExceptionInformation()))
               {
                  wsprintf( szBuffer, "Execution of except block for OUR_EXCEPTION." );
                  MessageBox( hWnd, szBuffer, "Except Block", MB_OK );
               }
               ReleaseDC(hWnd, hDC);
            }
            break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
            break;
      }
      break;
      case WM_DESTROY:
         PostQuitMessage(0);
      break;
      default:
         return (DefWindowProc(hWnd, uMsg, wParam, lParam));
   }
   return (NULL);
}