#include "pch.h"
#include <locale.h>
#include <string>
#include <iostream>

using namespace std;
#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	string content;
	char line[0x100] = { 0 };
	FILE* pFile = fopen("book.txt", "r");
	if (!pFile)
	{
		return -1;
	}
	while (fgets(line, 0x100, pFile) != NULL)
	{
		content += line;
	}
	cout << content << endl;
	fclose(pFile);

	return 0;
}
