#include <Windows.h>
#include <tchar.h>

int _cdecl MessageBoxPrintf(PTSTR szCaption, PTSTR szFormat, ...)
{
	TCHAR		szBuffer[100];
	va_list		pArgList;

	va_start(pArgList, szFormat);

	// _CRT_SECURE_NO_WARNINGS
	_vsntprintf_s(szBuffer, sizeof(szBuffer) / sizeof(TCHAR),
		sizeof(szBuffer) / sizeof(TCHAR),
		szFormat, pArgList);

	va_end(pArgList);

	return MessageBox(NULL, szBuffer, szCaption, MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR szCmdLine, int iCmdShow)
{
	int x, y;

	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);

	MessageBoxPrintf(TEXT("ÆÁÄ»³ß´ç"),
		TEXT("The Screen is %i pixels wide by %i pixels high."),
		x, y);

	return 0;
}