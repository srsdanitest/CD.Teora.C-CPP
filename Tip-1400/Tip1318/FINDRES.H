#define IDM_EXIT           100
#define IDM_TEST           200
#define IDM_ABOUT          301

typedef struct
{
   SHORT Value1;
   SHORT Value2;
   SHORT Value3;
}RESDATA;


LRESULT CALLBACK WndProc  (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About    (HWND, UINT, WPARAM, LPARAM);
