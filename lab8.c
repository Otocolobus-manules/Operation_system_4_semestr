#include <windows.h>
#include <stdio.h>
#include <conio.h>

HANDLE hthread[6], hsm, hsm1;
char buffer[12], buff[12];

void GoToXY(const int X, const int Y) {
    HANDLE OutputHandle;
    CONSOLE_SCREEN_BUFFER_INFO ScreenBufInfo;
    OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(OutputHandle, &ScreenBufInfo);
    ScreenBufInfo.dwCursorPosition.X = X;
    ScreenBufInfo.dwCursorPosition.Y = Y;
    SetConsoleCursorPosition(OutputHandle, ScreenBufInfo.dwCursorPosition);
}

DWORD WINAPI Writer(void* n) {
    short i;
    while (1) {
        WaitForSingleObject(hsm, 3000);
        if ((int)n == 3) {
            strncpy(buff, "Novosibirsk", 12);
        } else if ((int)n == 4) {
            strncpy(buff, "Ekaterinburg", 12);
        } else if ((int)n == 5) {
            strncpy(buff, "Semipalatink", 12);
        }
        for (i = 0; i <= 5; i++) {
            buffer[i] = buff[i];
        }
        Sleep(1000);
        for (i = 6; i <= 11; i++) {
            buffer[i] = buff[i];
        }
        ReleaseSemaphore(hsm1, 1, NULL);
    }
    return 0;
}

DWORD WINAPI Reader(void* n) {
    short i = 0, j;
    while (1) {
        i++;
        WaitForSingleObject(hsm1, INFINITE);
        GoToXY(((int)n + 1) * 20, i);
        printf("%s", buffer);
        ReleaseSemaphore(hsm, 1, NULL);
        Sleep(290);
    }
    return 0;
}

void main() {
    int i;
    system("cls");
    hsm = CreateSemaphore(NULL, 0, 1, NULL);
    hsm1 = CreateSemaphore(NULL, 0, 1, NULL);
    for (i = 3; i <= 5; i++) {
        hthread[i] = CreateThread(NULL, 4096, Writer, (void*)i, 0, NULL);
    }
    for (i = 0; i <= 2; i++) {
        hthread[i] = CreateThread(NULL, 4096, Reader, (void*)i, 0, NULL);
    }
    ReleaseSemaphore(hsm, 1, NULL);
    getchar();
    for (i = 0; i <= 5; i++) CloseHandle(hthread[i]);
    CloseHandle(hsm);
}