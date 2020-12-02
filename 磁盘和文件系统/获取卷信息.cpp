#include "pch.h"

#include <iostream>
#include <locale.h>

using namespace std;
#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");

	wchar_t wRootPathName[MAX_PATH] = { 0 };
	wcscat(wRootPathName, L"D:\\");
	wchar_t wVolumeNameBuffer[MAX_PATH] = { 0 };
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximumComponentLength;
	DWORD dwFileSystemFlags;
	wchar_t wFileSystemNameBuffer[MAX_PATH] = { 0 };
	BOOL bRet;
	bRet = GetVolumeInformation(wRootPathName, wVolumeNameBuffer, MAX_PATH, &dwVolumeSerialNumber, &dwMaximumComponentLength, &dwFileSystemFlags, wFileSystemNameBuffer, MAX_PATH);
	if (!bRet)
	{
		printf("error:%d\n", GetLastError());
		return -1;
	}
	wprintf(L"当前显示的逻辑卷为：%s\n", wRootPathName);
	wprintf(L"卷标: %s\n", wVolumeNameBuffer);
	// printf("%S\n", wVolumeNameBuffer); 对于宽字符，可使用%S进行格式化输出
	wprintf(L"卷序列号：%lu\n", dwVolumeSerialNumber);
	wprintf(L"文件系统：%s\n", wFileSystemNameBuffer);
	printf("最大文件名长度（不包括后缀）%lu\n", dwMaximumComponentLength);
	/*判断卷属性*/
	if (dwFileSystemFlags & FILE_VOLUME_QUOTAS)
	{
		wprintf(L"支持磁盘配额...\n");
	}
	if (dwFileSystemFlags & FILE_PERSISTENT_ACLS)
	{
		printf("支持...\n");
	}
	/*进行与操作如果支持就会返回常量对象的值*/
	wcout << hex << (dwFileSystemFlags & FILE_PERSISTENT_ACLS ) << endl;
	return 0;
}