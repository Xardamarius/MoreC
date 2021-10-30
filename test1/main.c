#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

int main()
{

    HWND hwnd = GetConsoleWindow();
    HDC dc = GetDC(hwnd);

    int i = 0;
    char c[1024];
    do
    {
        i++;
        SelectObject( dc, GetStockObject(DC_BRUSH));
        SetDCBrushColor( dc, RGB(255, 255, 255));
        SelectObject( dc, GetStockObject(DC_PEN));
        SetDCPenColor( dc, RGB(255, 0, 255));
        Rectangle(dc, 0, 0, 640, 300);

        SelectObject( dc, GetStockObject(DC_BRUSH));
        SetDCBrushColor( dc, RGB(0, 255, 0));
        Rectangle(dc, 0+i, 0, 100+i, 100);

        sprintf(c, "My super text!!!");
        TextOutA(dc, 20,50, c, strlen(c) + 1);

        Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}


/*
#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

int main()
{

    HWND hwnd = GetConsoleWindow();
    HDC dc = GetDC(hwnd);

    do
    {
        SelectObject( dc, GetStockObject(DC_BRUSH));
        SetDCBrushColor( dc, RGB(255, 255, 255));
        SelectObject( dc, GetStockObject(DC_PEN));
        SetDCPenColor( dc, RGB(255, 0, 255));
        Rectangle(dc, 0, 0, 640, 300);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
*/

/*
#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

int main()
{

    HWND hwnd = GetDesktopWindow();

    HDC dc = GetDC(hwnd);

    SelectObject( dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor( dc, RGB(255, 0, 255));
    Rectangle(dc, 10, 10, 110, 110);
    Ellipse(dc, 1000, 100, 1100, 210);

    return 0;
}
*/

/*
#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

int main()
{

    HWND hwnd = GetConsoleWindow();

    HDC dc = GetDC(hwnd);

    SelectObject( dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor( dc, RGB(255, 0, 255));
    Rectangle(dc, 10, 10, 110, 110);
    Ellipse(dc, 200, 100, 300, 200);

    return 0;
}
*/
