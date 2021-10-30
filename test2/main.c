#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

int main()
{
    HWND hwnd = GetConsoleWindow();

    LPPOINT pPnt;
    pPnt = malloc( sizeof(*pPnt) );

    LPRECT rct;
    rct = malloc( sizeof(*rct) );
    GetClientRect(hwnd, rct);

    LPRECT rctScr;
    rctScr = malloc( sizeof(*rctScr) );
    GetClientRect(GetDesktopWindow(), rctScr);

    do
    {
        system("cls");

        GetCursorPos(pPnt);
        printf("\n Global cursor pos: %d, %d\n", pPnt[0].x, pPnt[0].y);

        ScreenToClient(hwnd, pPnt);
        printf("\n Local cursor pos: %d, %d\n", pPnt[0].x, pPnt[0].y);

        printf("\n Client size: %d x %d\n", rct[0].right, rct[0].bottom);

        printf("\n Screen size: %d x %d\n", rctScr[0].right, rctScr[0].bottom);

        if (GetKeyState(VK_LBUTTON) < 0)
            printf("\n Left Mouse Button is down!!!\n");

        Sleep(100);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
