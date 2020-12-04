#include "pch.h"

VOID CreateConsole(CONST CHAR* ConsoleTitle, CONST CHAR* colorCmd, int x, int y, int cx, int cy);
VOID StartHook();

BOOL APIENTRY DllMain(_In_ void* _DllHandle, _In_ unsigned long _Reason, _In_opt_ void* _Reserved)
{
	switch (_Reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		CreateConsole(NULL, "color 20", 100, 100, 400, 800);
		printf("注入成功...\n");
		StartHook();
		printf("hook succeed...\n");
		break;
	}
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}
