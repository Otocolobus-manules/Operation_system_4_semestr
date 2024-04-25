#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD rc;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    printf("\n");
    printf("I am child1 %s!\n", argv[1]);
    Sleep(120);
    rc = (CreateProcess(NULL,"grandchild1.exe Evgeshka", 0, 0, 0, NORMAL_PRIORITY_CLASS, 0, 0, &si, &pi));
    if(!rc)
    {
        printf("Error create process (Grandchild Evgeshka)");
        getchar();
        return 0;
    }
    printf("\n");

    for(int i=0; i<15; i++){
        printf("I am child1. My name is Jimmy, my number=%d\n", i);
        Sleep(1300);
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}