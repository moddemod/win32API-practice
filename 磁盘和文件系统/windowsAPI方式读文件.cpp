#include "pch.h"
#include <locale.h>

using namespace std;
#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	HANDLE hFile = CreateFile(
		L"book.txt",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("error code:%d\n", GetLastError());
		return -1;
	}
	CHAR szBuffer[0x100] = { 0 };
	DWORD dwNumberOfBytesRead; /*读入的字节数*/
	BOOL bRet = ReadFile(
		hFile,
		szBuffer,
		0x100,
		&dwNumberOfBytesRead,
		NULL
	);
	if (!bRet)
	{
		printf("error code:%d\n", GetLastError());
		CloseHandle(hFile);
		return -1;
	}
	printf("%s\n", szBuffer);
	CloseHandle(hFile);

	return 0;
}
