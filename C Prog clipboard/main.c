#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <locale.h>


void TextFromClipboard(char **text)
{
    if (IsClipboardFormatAvailable(CF_TEXT))
    {
        if (OpenClipboard(0))
        {
            char *hBuff = GetClipboardData(CF_TEXT);
            int len = strlen(hBuff)+1;
            *text = realloc(*text, len);
            sprintf(*text, "%s", hBuff);
            CloseClipboard();

            printf("%s\n", *text);
        }
    }
}

void TextToClipboard(char *text)
{
    if (OpenClipboard(0))
    {
        EmptyClipboard();
        char *hBuff = GlobalAlloc(GMEM_FIXED, strlen(text)+1);
        strcpy(hBuff, text);
        SetClipboardData(CF_TEXT, hBuff);
            HANDLE *lcid = GlobalAlloc(GMEM_FIXED, sizeof(DWORD));
            *lcid = MAKELCID( MAKELANGID(LANG_RUSSIAN, SUBLANG_NEUTRAL), SORT_DEFAULT );
            SetClipboardData(CF_LOCALE, lcid);
        CloseClipboard();

        printf("text in clipboard\n");
    }
}

int main()
{
    HWND hwnd = GetConsoleWindow();
    char *str = NULL;
    setlocale(LC_ALL, "Russian"); //?????? ??????????!!!
    SetConsoleCtrlHandler(NULL, TRUE);

    while (1)
    {
        if (GetForegroundWindow() != hwnd) continue;
        if (GetKeyState(VK_F2) < 0) break;
        if (GetKeyState(VK_LCONTROL) < 0);
        {
            if (GetKeyState('V') < 0)
            {
                TextFromClipboard(&str);
                while (GetKeyState('V') < 0);
            }

            if (GetKeyState('C') < 0)
            {
                TextToClipboard(str);
                while (GetKeyState('C') < 0);
            }
        }
    }

    return 0;
}
