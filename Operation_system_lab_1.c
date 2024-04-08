#include <windows.h>
#include <stdio.h>

int main()
{
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hstdin == INVALID_HANDLE_VALUE || hstdout == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Error handler\n");
		return 1;
	}

	printf("Standard Input Handle: %lu\n", hstdin);
	printf("Standard Output Handle: %lu\n", hstdout);

	printf("Enter text: ");

	char buffer[100];
	DWORD bytesRead;

	if (ReadFile(hstdin, buffer, sizeof(buffer), &bytesRead, NULL))
	{
		printf("You have entered: %.*s\n", bytesRead, buffer);
	}
	else
	{
		fprintf(stderr, "Failed to read input\n");
			
		return 1;
	}

	getchar();
	return 0;
}
