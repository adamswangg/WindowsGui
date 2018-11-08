#include <Windows.h>
#include <stdio.h>

/**
 * Check the DLL dependency for these functions.
 *
 * crt standard version -> vcrt
 * max-length version -> vcrt
 * Windows version -> user32.dll
 */
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   PSTR szCmdLine,
				   int iCmdShow)
{
	
	char		szAsciiBuffer[100];
	wchar_t		szUnicodeBuffer[100];
	
	// crt standard version
	// _stprintf macro
	sprintf_s(szAsciiBuffer, 100, "sprintf is for 8-bit char");
	swprintf(szUnicodeBuffer, 100, L"swprintf is for 16-bit wchar");

	// Windows version
	// wsprintf macro
	wsprintfA(szAsciiBuffer, "wsprintfA is for 8-bit char");
	wsprintfW(szUnicodeBuffer, L"wsprintfW is for 16-bit wchar");

	// max-length version
	// _sntprintf macro
	_snprintf_s(szAsciiBuffer, 100, 100, "_snprintf is for 8-bit char");
	_snwprintf_s(szUnicodeBuffer, 100, 100, L"_snwprintf is for 16-bit wchar");


	// Pointer to Array of Arguments

	// CRT standard version
	// _vstprintf macro
	// ASCII: vsprintf
	// Unicode: vswprintf

	// Windows version
	// wvsprintf macro
	// ASCII: wvsprintA
	// Unicode: wvsprintfW

	// max-length version
	// _vsntprintf macro
	// ASCII: _vsnprintf
	// Unicode: _vsnwprintf



	return 0;
}