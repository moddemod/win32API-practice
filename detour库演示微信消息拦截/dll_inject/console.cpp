#include "pch.h"

#pragma warning(disable:4996)

/*关闭调试窗口*/
unsigned __stdcall ExitDetectionThread(VOID* pArg)
{
	while (TRUE)
	{
		if (GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(VK_F1)) /*Alt + F1 关闭*/
		{
			printf("即将关闭程序...\n");
			Sleep(50);
			PostMessage((HWND)pArg, WM_CLOSE, 0, 0);
			DWORD dwProcessId;
			GetWindowThreadProcessId((HWND)pArg, &dwProcessId);
			HANDLE hProcess = OpenProcess(THREAD_ALL_ACCESS, FALSE, dwProcessId);
			TerminateProcess(hProcess, 0);
			CloseHandle(hProcess);
		}
		Sleep(150);
	}
}

/*创建调试窗口*/
VOID CreateConsole(CONST CHAR* ConsoleTitle, CONST CHAR* colorCmd, int x, int y, int cx, int cy)
{
	setlocale(LC_ALL, "");
	AllocConsole();
	HWND hWnd = GetConsoleWindow();
	HANDLE hThread = (HANDLE)_beginthreadex(NULL,
		0,
		ExitDetectionThread,
		hWnd,
		0,
		0);
	if (hThread)
	{
		printf("123\n");
		CloseHandle(hThread);
	}
	/*设置窗口位置大小*/

	BOOL iRet = SetWindowPos(hWnd, HWND_TOP,
		0, 0,
		cx, cy,
		SWP_NOMOVE
	);
	if (!iRet)
	{
		printf("error code: %d\n", GetLastError());
	}
	iRet = SetWindowPos(hWnd, HWND_TOP,
		x, y,
		0, 0,
		SWP_NOSIZE
	);
	CloseHandle(hWnd);
	FILE* pIn = freopen("conin$", "r+t", stdin);
	if (!pIn)
	{
		return;
	}
	FILE* pOut = freopen("conout$", "w+t", stdout);
	if (!pOut)
	{
		return;
	}
	if (colorCmd)
	{
		system(colorCmd);
	}
	if (ConsoleTitle)
	{
		SetConsoleTitleA(ConsoleTitle);
	}
}
