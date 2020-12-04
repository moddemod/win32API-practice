#include "pch.h"

#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	BOOL bRet;
	//
	// 重命名或者移动文件名
	//
	CHAR szExistingFileName[MAX_PATH] = { 0 };
	strcat(szExistingFileName, "老文件名");
	CHAR szNewFileName[MAX_PATH] = { 0 };
	strcat(szNewFileName, "新文件名或者路径");

	bRet = MoveFile(szExistingFileName, szNewFileName); /*重命名或者移动文件，在同一目录下则为重命名文件*/
	if (!bRet)
	{
		printf("error code: %d\n", GetLastError()); /*2为系统找不到指定的文件*/
		return -1;
	}


	//
	// 删除文件
	//
	CHAR szFileName[MAX_PATH] = { 0 };
	strcat(szFileName, "需要删除的文件名");
	bRet = DeleteFile(szFileName);
	if (!bRet)
	{
		printf("error code: %d\n", GetLastError());
		return -1;
	}

	//
	// 复制文件
	//
	CHAR szExistingFileNameC[MAX_PATH] = { 0 };
	strcat(szExistingFileNameC, "欲进行复制的文件名");
	CHAR szNewFileNameC[MAX_PATH] = { 0 };
	strcat(szNewFileNameC, "复制后的文件名");
	bRet = CopyFile(szExistingFileNameC, szNewFileNameC, TRUE); /*第三个参数设置为TRUE如果存在文件就拷贝失败
																即不进行拷贝，如果设置为FALSE，文件不管存在与否都进行
																拷贝，显然这种情况下，如果存在文件就会覆盖原来的文件*/
	if (!bRet)
	{
		printf("error code: %d\n", GetLastError()); /*当错误号为0x50时，表示文件存在*/
		return -1;
	}
	return 0;
}
