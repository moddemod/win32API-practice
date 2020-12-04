#include "pch.h"

#pragma warning(disable:4996)
#pragma comment(linker, "/entry:mainCRTStartup /subsystem:console")


/*卸载hook*/
BOOL UnHook(HHOOK hHook)
{
	printf("卸载 hook\n");
	return UnhookWindowsHookEx(hHook);
}


typedef LRESULT(CALLBACK* pGetMsgProc)(int Code, WPARAM wParam, LPARAM lParam);
typedef HHOOK(*pStartHook)(HINSTANCE hMod, DWORD dwThreadId);

HHOOK hHook;

/*关闭调试窗口*/
unsigned __stdcall ExitDetectionThread(VOID* pArg)
{
	while (TRUE)
	{
		if (GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(VK_F1)) /*Alt + F1 关闭*/
		{
			UnHook(hHook);
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


int main()
{
	CreateConsole(NULL, "color 20", 100, 100, 400, 600);
	HWND hWnd = FindWindow("TXGuiFoundation", "QQ");
	DWORD dwProcessId; /*pid*/
	DWORD dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);
	printf("%d\n", dwProcessId);
	HMODULE hModule = LoadLibrary("test_dll.dll");
	if (!hModule)
	{
		return -1;
	}
	pGetMsgProc GetMsgProc = (pGetMsgProc)GetProcAddress(hModule, "GetMsgProc");
	pStartHook StartHook = (pStartHook)GetProcAddress(hModule, "StartHook");
	hHook = StartHook(hModule, dwThreadId);
	Sleep(500000);
	return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	CreateConsole("winmain调试控制台", "color 20", 50, 50, 300, 500);
	Sleep(50000000);
	return 0;
}
