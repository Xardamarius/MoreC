#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <windows.h>

LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (Msg == WM_DESTROY)
        PostQuitMessage(0);

    else if (Msg == WM_KEYDOWN)
    {
        if (wParam == VK_F2) PostQuitMessage(0);
        else if (wParam == '1')
        {
            SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
            SetWindowPos(hWnd, HWND_TOP, 0,0, 1280, 720, SWP_SHOWWINDOW);
        }
        else if (wParam == '2')
        {
            SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE);
            SetWindowPos(hWnd, HWND_TOP, 0,0, 640, 480, SWP_SHOWWINDOW);
        }
        else if (wParam == '3')
        {
            DEVMODE deviceMode;
            {
                deviceMode.dmSize = sizeof(deviceMode);
                deviceMode.dmPelsWidth = 800;
                deviceMode.dmPelsHeight = 600;
                deviceMode.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;
            }
            ChangeDisplaySettings(&deviceMode, CDS_FULLSCREEN);
        }
        else if (wParam == '4')
            ChangeDisplaySettings(0, 0);
        printf("code = %d\n", wParam);
    }

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
