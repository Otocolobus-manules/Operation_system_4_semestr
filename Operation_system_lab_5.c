#include <windows.h>
#include <stdio.h>


int main() {
    char* buffer;
    char symbol;
    DWORD bytesRead, bufferSize;
    HANDLE fileHandle, stdinHandle, stdoutHandle;
    INPUT_RECORD inputBuffer;
    COORD symbolCoord;

    fileHandle = CreateFile("f.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        return;
    }

    bufferSize = GetFileSize(fileHandle, NULL);
    buffer = (char*)malloc(bufferSize * sizeof(char));

    stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
    if (stdinHandle == INVALID_HANDLE_VALUE) {
        CloseHandle(fileHandle);
        return;
    }

    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdoutHandle == INVALID_HANDLE_VALUE) {
        CloseHandle(fileHandle);
        return;
    }

    ReadFile(fileHandle, buffer, bufferSize, &bytesRead, NULL);
    WriteFile(stdoutHandle, buffer, bytesRead, NULL, NULL);

    SetConsoleMode(stdinHandle, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    printf("\n");

    while (1) {
        if (ReadConsoleInput(stdinHandle, &inputBuffer, 1, &bytesRead)) {
            if (inputBuffer.EventType == MOUSE_EVENT) {
                if (inputBuffer.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
                    break;
                }

                if (inputBuffer.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    symbolCoord.X = inputBuffer.Event.MouseEvent.dwMousePosition.X;
                    symbolCoord.Y = inputBuffer.Event.MouseEvent.dwMousePosition.Y;

                    ReadConsoleOutputCharacter(stdoutHandle, &symbol, 1, symbolCoord, &bytesRead);

                    if (symbol != ' ') {
                        printf("%c (%d, %d)", symbol, symbolCoord.X, symbolCoord.Y);
                    }
                }
            }
        }
    }

    free(buffer);
    CloseHandle(fileHandle);
}
