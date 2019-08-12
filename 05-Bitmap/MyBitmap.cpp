#include<windows.h>
#include "MyBitmap.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MYICONAPP");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("BITMAP WINDOW"),
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

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HBITMAP hBitmap = NULL;
	PAINTSTRUCT ps;
	RECT rc;

	switch (iMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));
		if (hBitmap == NULL) {
			MessageBox(hwnd, TEXT("Could Not Load Bitmap!!"), TEXT("Error!"), MB_OK);
		}
		break;

	case WM_PAINT:
		BITMAP bitmap;
		HDC hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		HDC memoryHdc = CreateCompatibleDC(NULL);
		SelectObject(memoryHdc, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		 StretchBlt(hdc,
			260,
			100,
			bitmap.bmWidth,
			bitmap.bmHeight,
			memoryHdc,
			0,
			0,
			bitmap.bmWidth,
			bitmap.bmHeight,
			SRCCOPY);
	
		DeleteDC(memoryHdc);
		EndPaint(hwnd, &ps);
		break;

		return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
















