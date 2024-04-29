#define BUF_SIZE 15000
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

TCHAR szName[] = TEXT("Glavnaya");
TCHAR fMsg[] = TEXT("hello iz glavnoy");
TCHAR szMsg[] = TEXT("soobshenie iz pervogo");
LPCWSTR Semaphore = (LPCWSTR) "Семафор";

char AllocText[] = "abcdefghijklmno";

int main()
{
    system("cls");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    char buff[255];
    int len;
    HANDLE Console = GetStdHandle(STD_ERROR_HANDLE);
            len = sprintf(buff, "glavnaya programma\n");
    WriteFile(Console, buff, len, NULL, NULL);
    HANDLE hSemaphore = CreateSemaphore(NULL, 0, 1, Semaphore);

    HANDLE hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
    BUF_SIZE,
    szName);
            LPTSTR pBuf = (LPTSTR)MapViewOfFile(hMapFile,
                                                FILE_MAP_ALL_ACCESS,
                                                0,
                                                0,
                                                0);

    len = sprintf(buff, "vpiska pervogo soobsheniya v pamyat\n");
    WriteFile(Console, buff, len, NULL, NULL);
    CopyMemory((PVOID)pBuf, fMsg, (_tcslen(fMsg) * sizeof(TCHAR)));
    Sleep(2000);
    STARTUPINFO sInfo;
    PROCESS_INFORMATION pInfo;
    ZeroMemory(&sInfo, sizeof(STARTUPINFO));
    sInfo.cb = sizeof(sInfo);
    TCHAR path[MAX_PATH] = _T("programm.exe");
    if (CreateProcess(NULL, path, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,
                      NULL, &sInfo, &pInfo) == 0)
    {
        len = sprintf(buff, "file programm.exe ne naiden\n");
        WriteFile(Console, buff, len, NULL, NULL);
    }
    len = sprintf(buff, "jdite 10 sekund\n");
    WriteFile(Console, buff, len, NULL, NULL);
    Sleep(10000);
    len = sprintf(buff, "zapis:");
    WriteFile(Console, buff, len, NULL, NULL);
    len = sprintf(buff, "(soobsheniya iz pervogo processa v programmy)\n");
    WriteFile(Console, buff, len, NULL, NULL);
    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));

    ReleaseSemaphore(hSemaphore, 1, NULL);

    LPTSTR NewMem = (LPTSTR)VirtualAlloc(
            NULL,
            BUF_SIZE,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_READWRITE);

    if (NewMem != NULL)
    {
        len = sprintf(buff, "virtyalnaya pamyat sozdana\n");
        WriteFile(Console, buff, len, NULL, NULL);
    }
    else
    {
        len = sprintf(buff, "ne vishlo\n");
        WriteFile(Console, buff, len, NULL, NULL);
        _getch();
        return 1;
    }

    LPTSTR Address = NewMem;

    for (int i = 0; i < 15; i++)
    {
        CopyMemory((LPVOID)Address, (PVOID)AllocText, sizeof(char));
        len = sprintf(buff, "adress:");
        WriteFile(Console, buff, len, NULL, NULL);
        len = sprintf(buff, "0x%X", Address);
        WriteFile(Console, buff, len, NULL, NULL);
        printf("(0x%X) ", Address);
        len = sprintf(buff, "znacheie:");
        WriteFile(Console, buff, len, NULL, NULL);
        printf("Value: ");
        len = sprintf(buff, "(%c)\n", AllocText[i]);
        WriteFile(Console, buff, len, NULL, NULL);
        Address += 400; // сдвиг
        Sleep(200);
    }
    len = sprintf(buff, "\n\t nazmite chto nibyd dlyz zaversheniy");
    WriteFile(Console, buff, len, NULL, NULL);
    getchar();
    return 0;
}