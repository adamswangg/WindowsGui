#include "sysmets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR	  szCmdLine,
	int		  iCmdShow)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASSEX  wndclass;

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
	wndclass.lpszClassName = TEXT("SYSMETS2");
	wndclass.hIconSm = NULL;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx failed!"), TEXT("SYSMETS2"), MB_OK);
		return -1;
	}

	hwnd = CreateWindowEx(
		0,
		TEXT("SYSMETS2"),
		TEXT("Sysmets2 display window"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
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
	static int cxChar, cyChar, cxCaps;
	static int cyClient;
	static int iscrollPos;

	HDC				hdc;
	PAINTSTRUCT		ps;
	int				i, y;
	TCHAR			szBuffer[10];
	TEXTMETRIC		tm;

	switch (message)
	{
	case WM_CREATE:
		// text metrics init
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmExternalLeading + tm.tmHeight;
		cxCaps = tm.tmPitchAndFamily & 1 ? tm.tmAveCharWidth * 2 / 3: tm.tmAveCharWidth;
		ReleaseDC(hwnd, hdc);

		// scrollbar init
		iscrollPos = 0;
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - 1, TRUE);
		return 0;

	case WM_SIZE:
		cyClient = HIWORD(lParam);
		return 0;

	case WM_VSCROLL:
	{
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			iscrollPos--;
			break;
		case SB_LINEDOWN:
			iscrollPos++;
			break;
		case SB_THUMBPOSITION:
			iscrollPos = HIWORD(wParam);
			break;
		}
		// unsigned int VS signed int
		iscrollPos = max(min((int)(NUMLINES - 1), iscrollPos), 0);
		if (iscrollPos != GetScrollPos(hwnd, SB_VERT))
		{
			SetScrollPos(hwnd, SB_VERT, iscrollPos, TRUE);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		
		return 0;
	}

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0, y = 0; i < NUMLINES; i++)
		{
			y = cyChar * (i - iscrollPos);
			TextOut(hdc, 0, y, szBuffer, wsprintf(szBuffer, TEXT("%d"), GetSystemMetrics(sysmetrics[i].iIndex)));
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
