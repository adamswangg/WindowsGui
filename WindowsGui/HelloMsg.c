#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	int button_id;

	// Test return value of MessageBox function.
	button_id = MessageBoxW(NULL, L"Hello Msg", L"Hello Caption", MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONASTERISK);
	if (button_id == IDOK) {
		MessageBoxW(NULL, L"You select OK button", L"Show Button", MB_OK);
	}
	else if (button_id == IDCANCEL) {
		MessageBoxW(NULL, L"You select cancel button", L"Show Button", MB_OK);
	}

	return 0;
}
