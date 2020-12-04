#include "pch.h"
#include "detours.h"

#pragma comment (lib,"detours.lib")

/*原函数指针*/
int ( __stdcall *pTextOutW)(_In_ HDC hdc, _In_ int x, _In_ int y, _In_reads_(c) LPCWSTR lpString, _In_ int c) = TextOutW;

/*hook函数*/
int __stdcall MyTextOutW(_In_ HDC hdc, _In_ int x, _In_ int y, _In_reads_(c) LPCWSTR lpString, _In_ int c)
{
	if (c)
	{
		printf("%S\n", lpString);
	}
	return pTextOutW(hdc, x, y, lpString, c);
}

int (__stdcall *pExtTextOutA)(_In_ HDC hdc, _In_ int x, _In_ int y, _In_ UINT options, _In_opt_ CONST RECT* lprect, _In_reads_opt_(c) LPCSTR lpString, _In_ UINT c, _In_reads_opt_(c) CONST INT* lpDx) = ExtTextOutA;

int __stdcall MyExtTextOutA(_In_ HDC hdc, _In_ int x, _In_ int y, _In_ UINT options, _In_opt_ CONST RECT* lprect, _In_reads_opt_(c) LPCSTR lpString, _In_ UINT c, _In_reads_opt_(c) CONST INT* lpDx)
{
	if (c)
	{
		printf("%s\n", lpString);
	}
	return ExtTextOutA(hdc, x, y, options, lprect, lpString, c, lpDx);
}
/*开始hook*/
VOID StartHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)pTextOutW, MyTextOutW);
	DetourTransactionCommit();
}

/*解除hook*/
VOID EndHook()
{

}
