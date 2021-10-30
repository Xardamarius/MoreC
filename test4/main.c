#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

#define masSize 100
RECT mas[masSize];

RECT rct;

void FillMas()
{
    srand(5);
    for  (int i = 0; i < masSize; i++)
    {
        mas[i].left = rand() % 800 - 100;
        mas[i].top = rand() % 400;
        mas[i].right = mas[i].left + 100;
        mas[i].bottom = mas[i].top + 100;
    }
}

void WinMove()
{
    for  (int i = 0; i < masSize; i++)
    {
        mas[i].left += 3;
        if (mas[i].left > 700) mas[i].left = -100;
        mas[i].right = mas[i].left + 100;
        mas[i].bottom = mas[i].top + 100;
    }
}

void WinShow(HDC dc)
{
    HDC memDC = CreateCompatibleDC(dc);
    HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right - rct.left, rct.bottom - rct.top);
    SelectObject(memDC, memBM);

        SelectObject(memDC, GetStockObject(DC_BRUSH));
        SetDCBrushColor(memDC, RGB(255, 255, 255));
        Rectangle(memDC, 0,0, 640,480);

        SelectObject(memDC, GetStockObject(DC_BRUSH));
        SetDCBrushColor(memDC, RGB(0, 255, 0));
        SelectObject(memDC, GetStockObject(DC_PEN));
        SetDCPenColor(memDC, RGB(255, 0, 0));
        for (int i = 0; i < masSize; i++)
            Rectangle(memDC, mas[i].left, mas[i].top, mas[i].right, mas[i].bottom);

    BitBlt(dc, 0,0, rct.right - rct.left, rct.bottom - rct.top, memDC, 0,0, SRCCOPY);
    DeleteDC(memDC);
    DeleteObject(memBM);
}

LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (Msg == WM_DESTROY)
        PostQuitMessage(0);

    else if (Msg == WM_KEYDOWN)
        printf("code = %d\n", wParam);

    else if (Msg == WM_CHAR)
        printf("%c\n", wParam);

    else if (Msg == WM_SIZE)
        GetClientRect(hWnd, &rct);

    else if (Msg == WM_MOUSEMOVE)
    {
        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);
        printf("mouse [%d,%d]\n", xPos, yPos);
    }

    else if (Msg == WM_LBUTTONDOWN)
        printf("mouse Left Button Down\n");

    else return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

int main()
{
    WNDCLASSA wcl;
        memset(&wcl, 0, sizeof(WNDCLASSA) );
        wcl.lpszClassName = "my Window";
        wcl.lpfnWndProc = WndProc;
    RegisterClassA(&wcl);

    HWND hwnd;
    hwnd = CreateWindow("my Window", "Window Name", WS_OVERLAPPEDWINDOW,
                        10,10, 640,480, NULL, NULL, NULL, NULL);
    HDC dc = GetDC(hwnd);

    ShowWindow(hwnd, SW_SHOWNORMAL);

    FillMas();

    MSG msg;
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            WinMove();
            WinShow(dc);
            Sleep(5);
        }
    }
    return 0;
}
