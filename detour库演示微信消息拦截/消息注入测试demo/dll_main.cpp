#include "pch.h"

BOOL WINAPI  DllMain(_In_ void* _DllHandle, _In_ unsigned long _Reason, _In_opt_ void* _Reserved)
{
	switch (_Reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		printf("DLL_PROCESS_ATTACH\n");
		AllocConsole();
		OutputDebugString("这是调试消息");
		// MessageBox(NULL, TEXT("test"), TEXT("test"), MB_OK);
	}
		break;
	case DLL_PROCESS_DETACH:
		printf("DLL_PROCESS_DETACH\n");
		break;
	case DLL_THREAD_ATTACH:
		printf("DLL_THREAD_ATTACH\n");
		break;
	case DLL_THREAD_DETACH:
		printf("DLL_THREAD_DETACH\n");
		break;
	}
	return TRUE;
}

/*hook回调注册函数*/
//LRESULT CALLBACK HookProc(int code, WPARAM wParam, LPARAM lParam)
//{
//
//	return CallNextHookEx(NULL, code, wParam, lParam);
//}




extern "C" __declspec(dllexport)LRESULT CALLBACK GetMsgProc(int Code, WPARAM wParam, LPARAM lParam)
{
	//
	//你自己对消息的处理
	//
	OutputDebugString("消息来了...\n");
	return CallNextHookEx(NULL, Code, wParam, lParam);
}

/*开始hook*/
extern "C" __declspec(dllexport) HHOOK StartHook(HINSTANCE hMod, DWORD dwThreadId)
{
	HHOOK hHook = SetWindowsHookEx(WH_CBT, GetMsgProc, hMod, dwThreadId);
	if (!hHook)
	{
		printf("hook failed... %d\n", GetLastError());
		return 0;
	}
	printf("hook succeed\n");
	return hHook;
}
