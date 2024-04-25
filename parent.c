#include <windows.h>
#include <stdio.h>
int main()
{
    DWORD rc;
    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    memset(&si1, 0, sizeof(STARTUPINFO));
    si1.cb = sizeof(si1);

    memset(&si2, 0, sizeof(STARTUPINFO));
    si2.cb = sizeof(si2);

    rc = CreateProcess(NULL, "child1.exe Tim", NULL, NULL, FALSE,
                       NORMAL_PRIORITY_CLASS, NULL, NULL, &si1, &pi1);
    if (!rc)
    {
        printf("Error create Process, codeError = %ld\n", GetLastError());
        getchar();
        return 0;
    }
    printf("Child1 process:\n");
    printf("hProcess=%d hThread=%d ProcessId=%ld ThreadId=%ld\n", pi1.hProcess, pi1.hThread, pi1.dwProcessId, pi1.dwThreadId);
    Sleep(100);
    rc = CreateProcess(NULL, "child2.exe Jack", NULL, NULL, FALSE,
                       NORMAL_PRIORITY_CLASS, NULL, NULL, &si2, &pi2);
    if (!rc)
    {
        printf("Error create Process, codeError = %ld\n", GetLastError());
        getchar();
        return 0;
    }
    printf("Child2 process:\n");
    printf("hProcess=%d hThread=%d ProcessId=%ld ThreadId=%ld\n", pi2.hProcess, pi2.hThread, pi2.dwProcessId, pi2.dwThreadId);
    Sleep(110);
    HANDLE job = CreateJobObject(NULL, NULL);
    AssignProcessToJobObject(job, pi2.hProcess);

    for (int i=0; i<12; i++) {
        if(i == 7) {
            TerminateProcess(pi1.hProcess, 0);
            printf("Child1 - Tim was killed\n");
        }
        if(i == 11) {
            TerminateJobObject(job, 0);
            printf("Child2 - Jack was killed\n");
        }
        printf("I am Parent... (my K=%d)\n", i);
        Sleep(1000);

    }
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);
    getchar();
    return 0;
}