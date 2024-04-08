#include <windows.h> 
void main()
 {char buffer[100]="It was readed:"; 
 DWORD len, actlen; 
 HANDLE hstdin, fhandle; 
 char fname[ ]="Test.txt"; 
 BOOL rc;
 len = strlen(buffer);  
 hstdin = GetStdHandle(STD_INPUT_HANDLE);
 if (hstdin == INVALID_HANDLE_VALUE) return; 
 fhandle=CreateFile(fname, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0); 
 if (fhandle ==INVALID_HANDLE_VALUE) return; 
 rc=ReadFile(hstdin, buffer+len, 80, &actlen, NULL); 
 if (!rc) return;
 WriteFile(fhandle, buffer, len+actlen, &actlen, NULL); 
 CloseHandle(fhandle);
}