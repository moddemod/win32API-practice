#include "pch.h"

#include <iostream>
#include <fstream>

#include <locale.h>

using namespace std;
#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	ifstream ifs("book.txt");
	if (!ifs)
	{
		return -1;
	}
	string content;
	char line[0x100] = { 0 };
	while (ifs.getline(line, 0x100))
	{
		content += line;
		content += "\r\n";
	}
	cout << content << endl;
	ifs.close();

	return 0;
}
