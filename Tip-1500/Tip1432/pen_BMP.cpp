HBITMAP hBitmap;
HDC			hDC;
HDC			hMemDC;

//  Load the bitmap into memory

hBitmap = LoadBitmap( hInst, "pen" );

//  Paint the bitmap onto the MemDC and then the screen

hDC = GetDc( hWnd );
hMemDC = CreateCompatibleDC( hDC);
SelectObject( hMemDC, hBitmap );
BitBlt( hDC, 10, 10, 60, 60, hMemDC, 0, 0, SRCCOPY );
DeleteDC( hMemDC );
ReleaseDC( hWnd, hDC );
DeleteObject( hBitmap );