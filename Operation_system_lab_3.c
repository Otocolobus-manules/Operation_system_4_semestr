#include <windows.h>
#include <stdio.h>
#include <winerror.h>
#include <locale.h>

int main() {
    char buffer[100] = "";
    DWORD actlen;
    HANDLE hstdout, fhandle;
    char fname[9] = "test.txt";
    BOOL rc;
    BOOL open = FALSE;
    COORD cd_1, cd_2, cd_3, cd_4;
    const DWORD size = 100 + 1;
    char lpszBuffer[size];
    cd_1.X = 50;
    cd_1.Y = 13;
    cd_2.X = 12;
    cd_2.Y = 14;
    cd_3.X = 45;
    cd_3.Y = 13;
    cd_4.X = 50;
    cd_4.Y = 14;
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hstdout == INVALID_HANDLE_VALUE) return 1;
    do
    {
        fhandle = CreateFile(fname, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fhandle == INVALID_HANDLE_VALUE)
        {
            DWORD Err = GetLastError();
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, Err, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPTSTR)&lpszBuffer, size, NULL);
            system("cls");
            SetConsoleCursorPosition(hstdout, cd_1);
            SetConsoleTextAttribute(hstdout, FOREGROUND_RED);
            printf("Error Code: 
            SetConsoleCursorPosition(hstdout, cd_2);
            printf("Error Name: 
            Sleep(2000);
        }
        else
            open = TRUE;
     while (open == FALSE);
    rc = ReadFile(fhandle, buffer, 80, &actlen, NULL);
    if (!rc) return 1;
    system("cls");
    SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN);
    SetConsoleCursorPosition(hstdout, cd_3);
    printf("File opened successfully");
    SetConsoleCursorPosition(hstdout, cd_4);
    WriteFile(hstdout, buffer, actlen, &actlen, NULL);
    getchar();
    CloseHandle(fhandle);

    return 0;