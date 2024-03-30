#include <windows.h>
#include <stdio.h>

void main(){
	char enter_text[13] = "Enter text:\n";
	char buffer[80] = "copy text: ";

	byte len_e, len_b;

	DWORD actlen;
	HANDLE hstdin, hstdout;
    HANDLE iFile, oFile;
	BOOL rc;

    iFile = CreateFileA(
            "F:\\Programming\\GitHub_Reposit\\Operation_system\\InputFile.txt",
            GENERIC_READ,
            0, NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    oFile = CreateFileA(
            "F:\\Programming\\GitHub_Reposit\\Operation_system\\OutputFile.txt",
            GENERIC_WRITE,
            0, NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

	len_b = strlen(buffer);
	len_e = strlen(enter_text);

	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hstdout == INVALID_HANDLE_VALUE)ExitProcess(0);

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hstdin == INVALID_HANDLE_VALUE)ExitProcess(0);

	printf("Output handle %i\n", hstdout);
	fflush(stdout);
	printf("Input handle %i\n", hstdin);
	fflush(stdout);

	WriteFile(hstdout, enter_text, len_e, NULL, 0);
	rc = ReadFile(iFile, buffer + len_b, 80, &actlen, NULL);
	if (!rc)ExitProcess(0);
	actlen += len_b;
	WriteFile(oFile, buffer, actlen, &actlen, 0);

    CloseHandle(iFile);
    CloseHandle(oFile);

	ExitProcess(0);
}