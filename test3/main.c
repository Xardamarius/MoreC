#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (Msg == WM_DESTROY)
        PostQuitMessage(0);

    else if (Msg == WM_KEYDOWN)
        printf("code = %d\n", wParam);

    else if (Msg == WM_CHAR)
        printf("%c\n", wParam);

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

    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

int main()
{
    WNDCLASSA wcl;
        memset(&wcl, 0, sizeof(WNDCLASSA) );
        wcl.lpszClassName = "my Window";
        wcl.lpfnWndProc = DefWindowProcA;
    RegisterClassA(&wcl);

    HWND hwnd;
    hwnd = CreateWindow("my Window", "Window Name", WS_OVERLAPPEDWINDOW,
                        10,10, 640,480, NULL, NULL, NULL, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
        printf("%d %d\n", msg.message, msg.wParam);
        if ((msg.message == 161) && (msg.wParam == 20))
            return 0;
    }

    return 0;
}
*/
