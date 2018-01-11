#include <genstub.c>

// Windows message procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
       case WM_COMMAND:       // Process menu items.
               switch ( LOWORD( wParam )  )
               {
                  case IDM_TEST:
                    {
                       TCHAR szBuffer[128];
                       DWORD dwBaseAddr;
                       LDT_ENTRY ldtEntry;
                       CONTEXT context;
                       context.ContextFlags = CONTEXT_FULL;
                       GetThreadContext( GetCurrentThread(), &context );
                       GetThreadSelectorEntry( GetCurrentThread(), context.SegDs,
                                               &ldtEntry );
                       dwBaseAddr = ldtEntry.BaseLow +
                                    (DWORD) ldtEntry.HighWord.Bits.BaseMid << 8 +
                                    (DWORD) ldtEntry.HighWord.Bits.BaseHi << 16;
                       wsprintf( szBuffer,
                                 "LDT entry for %lX. Base = %lX, Type = %X, Priv = %X ",
                                 context.SegDs, dwBaseAddr, ldtEntry.HighWord.Bits.Type,
                                 ldtEntry.HighWord.Bits.Dpl );
                       MessageBox( hWnd, szBuffer, "Thread Selector Entry", MB_OK );
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
          break;
       default:
            return DefWindowProc( hWnd, uMsg, wParam, lParam );
   }
   return NULL;
}