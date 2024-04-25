#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[])
{
    printf("\n");
    printf("Hi this is %s (grandhicld1)\n", argv[1]);
    Sleep(150);
    for (int i = 0; i < 15; i++)
    {
        printf("Grandchild 1 %s: %i ---\n",argv[1], i);
        Sleep(1700);
    }
    return 0;
}