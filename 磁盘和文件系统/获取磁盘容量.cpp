#include "pch.h"

#include <iostream>
#include <locale.h>

using namespace std;
#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	wchar_t wRootPathName[MAX_PATH] = { 0 };
	wcscat(wRootPathName, L"C:\\");
	DWORD dwSectorPerCulster; /*每簇扇区数*/
	DWORD dwBytesPerSector; /*每扇区字节数*/
	DWORD dwNumberOfFreeClusters; /*空闲簇*/
	DWORD dwTotalNumberOfClusters; /*总簇*/

	BOOL bRet = GetDiskFreeSpace(wRootPathName, &dwSectorPerCulster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);
	if (!bRet)
	{
		printf("error: %d\n", GetLastError());
		return -1;
	}
	printf("总簇数：%lu\n", dwTotalNumberOfClusters);
	printf("空闲簇数：%lu\n", dwNumberOfFreeClusters);
	printf("每簇扇区数：%lu\n", dwSectorPerCulster);
	printf("每扇区字节数：%lu\n", dwBytesPerSector);
	/*下面4行在win10上面测试不准确，*/
	DWORD dwBytesTotalSpace = dwTotalNumberOfClusters * dwSectorPerCulster * dwBytesPerSector;
	DWORD dwBytesFreeSpace = dwNumberOfFreeClusters * dwSectorPerCulster * dwBytesPerSector;
	printf("磁盘总容量大小：%lu字节\n", dwBytesTotalSpace);
	printf("磁盘空闲容量大小：%lu字节\n", dwBytesFreeSpace);

	/*获取容量推荐使用下面API*/
	wchar_t wDirectoryName[MAX_PATH] = { 0 };
	wcscat(wDirectoryName, L"C:\\");
	ULARGE_INTEGER FreeBytesAvailableToCaller;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;

	bRet = GetDiskFreeSpaceEx(wDirectoryName, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
	if (!bRet)
	{
		printf("error: %d", GetLastError());
		return -1;
	}
	printf("磁盘总容量大小：%llu\n", TotalNumberOfBytes.QuadPart);
	printf("磁盘空闲容量大小：%llu\n", TotalNumberOfFreeBytes.QuadPart);
	// 总共的空间
	cout << (TotalNumberOfBytes.QuadPart >> 20) << endl; /*多少M*/
	cout << (TotalNumberOfBytes.QuadPart >> 30) << endl; /*多少G*/

	// 空闲的空间
	cout << (TotalNumberOfFreeBytes.QuadPart >> 20) << endl; /*多少M*/
	cout << (TotalNumberOfFreeBytes.QuadPart >> 30) << endl; /*多少G*/

	// 与调用线程关联的用户在磁盘上可用空间
	cout << (FreeBytesAvailableToCaller.QuadPart >> 30) << endl; /*G*/

	return 0;
}
