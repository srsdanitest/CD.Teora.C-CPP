#include <genstub.c>

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{

   switch (uMsg)
   {
         case WM_COMMAND:
               switch ( LOWORD( wParam ) )
               {
                     case IDM_TEST:
                     {
                           SYSTEM_INFO si;
                           char        szBuffer[128];
                           HDC         hDC = GetDC( hWnd );

                           GetSystemInfo( &si );
                           // Report system info.
                           wsprintf( szBuffer, "OEM Id: %X, Addr Range %lX-%lX",
                                     si.dwOemId, si.lpMinimumApplicationAddress,
                                     si.lpMaximumApplicationAddress);
                           TextOut( hDC, 0, 0, szBuffer, lstrlen(szBuffer ) );
                           wsprintf( szBuffer, "Page Size: %lX, Allocation: %lX",
                                     si.dwPageSize, si.dwAllocationGranularity );
                           TextOut( hDC, 0, 20, szBuffer, lstrlen(szBuffer ) );
                           // Just test for Intel x86 chips. Windows 95 does not run
                           // on the RISC-based architectures.
                           wsprintf( szBuffer, "Type of Processor: %s",
                                   ( si.dwProcessorType == PROCESSOR_INTEL_386 ) ?
                                   "386" :
                                   ( ( si.dwProcessorType == PROCESSOR_INTEL_486 ) ?
                                   "486" : "PENTIUM" ) );
                           TextOut( hDC, 0, 40, szBuffer, lstrlen(szBuffer ) );
                           ReleaseDC( hWnd, hDC );
                           return 0;
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