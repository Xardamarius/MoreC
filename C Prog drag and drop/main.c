#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

void DropFile(HDROP hDrop)
{
    char fName[MAX_PATH];
    int cnt = DragQueryFile(hDrop, 0xffffffff, NULL, 0);
    printf(" %d\n", cnt);

    POINT pt;
    DragQueryPoint(hDrop, &pt);
    printf("  (%d,%d)\n", pt.x, pt.y);

    for (int i = 0; i < cnt; i++)
    {
        DragQueryFile(hDrop, i, fName, MAX_PATH);
        printf("   %s\n", fName);
    }
    DragFinish(hDrop);
}

LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (Msg == WM_DESTROY)
        PostQuitMessage(0);

    else if (Msg == WM_DROPFILES)
        DropFile(wParam);

    else if (Msg == WM_KEYDOWN)
        printf("code = %d\n", wParam);

    else if (Msg == WM_CHAR)
        printf("%c\n", wParam);

    else if (Msg == WM_MOUSEMOVE)
    {
        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);
        //printf("mouse [%d,%d]\n", xPos, yPos);
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

    ShowWindow(hwnd, SW_SHOWNORMAL);
    DragAcceptFiles(hwnd, TRUE);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
