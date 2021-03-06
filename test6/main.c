#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINN 0x0A00

#include <windows.h>

#define bt2_id 2
#define edt1_id 3
#define cb1_id 4

HWND bt_quit;
HWND cap1;
HWND CB;

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

    else if (Msg == WM_COMMAND)
    {
        printf("WM_COMMAND\n");

        if (bt_quit == lParam)
            PostQuitMessage(0);

        if (LOWORD(wParam) == bt2_id)
            printf("bt2 pressed\n");

        if (LOWORD(wParam) == edt1_id)
        {
            int nc = HIWORD(wParam);
            char c[100];
            GetWindowText(lParam, c, 100);
            if (nc == EN_UPDATE)
                SetWindowText(cap1, c);
            if (nc == EN_CHANGE)
                printf("   EN_UPDATE\n");
        }

        if (LOWORD(wParam) == cb1_id)
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int id = SendMessage(lParam, CB_GETCURSEL, 0, 0);
                char c[100];
                GetWindowText(lParam, c, 100);
                printf("   old - %s\n", c);
                SendMessage(lParam, CB_GETLBTEXT, id, c);
                printf("   new - %s\n", c);
            }
        }

    }


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

    bt_quit = CreateWindow("button", "Quit",
                          WS_VISIBLE | WS_CHILD,
                          10,10, 100,50,
                          hwnd, NULL, NULL, NULL);

    HWND bt2 = CreateWindow("button", "sdfsdfsdf",
                          WS_VISIBLE | WS_CHILD,
                          110,10, 100,50,
                          hwnd, bt2_id, NULL, NULL);

    HWND edt = CreateWindow("edit", "0",
                          WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER,
                          50,80, 60,20,
                          hwnd, edt1_id, NULL, NULL);

    cap1 = CreateWindow("static", "ioioioioio",
                          WS_VISIBLE | WS_CHILD,
                          200,80, 120,20,
                          hwnd, NULL, NULL, NULL);

    CB = CreateWindow("combobox", "",
                          WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                          210,10, 100,150,
                          hwnd, cb1_id, NULL, NULL);

        SendMessage(CB, CB_ADDSTRING, 0, "wewewewe");
        SendMessage(CB, CB_ADDSTRING, 0, "ioioioi");
        SendMessage(CB, CB_ADDSTRING, 0, "12123434");
        SendMessage(CB, CB_SETCURSEL, 1, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
