#include "sysmets.h"

static TCHAR WNDCLASSNAME[] = TEXT("SYSMETS1");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = WNDCLASSNAME;
	wndclass.hIconSm = NULL;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx failed!"), TEXT("SysMets1"), MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		0,
		WNDCLASSNAME,
		TEXT("SysMets Main Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cxCaps, cyChar;
	static int cxClient, cyClient;
	static TCHAR szBuffer[200];

	HDC hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;

	int iLength;

	switch (message)
	{
		case WM_CREATE:
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
			ReleaseDC(hwnd, hdc);
			return 0;

		case WM_SIZE:
			cxChar = LOWORD(lParam);
			cyChar = HIWORD(lParam);
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			for (int i = 0; i < NUMLINES; i++) {
				// may replace with code from book which out three columns
				iLength = wsprintf(szBuffer, TEXT("%-30s    %20d    %s"), sysmetrics[i].szLabel, GetSystemMetrics(sysmetrics[i].iIndex), sysmetrics[i].szDesc);
				TextOut(hdc, 0, cyChar * i, szBuffer, iLength);
			}
			EndPaint(hwnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	
	return DefWindowProc(hwnd, message, wParam, lParam);
}