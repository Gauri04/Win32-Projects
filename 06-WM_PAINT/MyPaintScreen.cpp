//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Colorful Screen Application"),
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
	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	static int iPaintFlag = 0;
	switch (iMsg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	case WM_CHAR :
		switch (LOWORD(wParam)) {
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'C':
		case 'c':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'Y':
		case 'y':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'M':
		case 'm':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'W':
		case 'w':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'K':
		case 'k':
		default:
			iPaintFlag = 8;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'a':
		case 'A':
			iPaintFlag = 9;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 'S':
		case 's':
			iPaintFlag = 10;
			InvalidateRect(hwnd, NULL, true);
			break;


		case 'D':
		case 'd':
			iPaintFlag = 11;
			InvalidateRect(hwnd, NULL, true);
			break;
		}
		break;

	case WM_PAINT :
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		HBRUSH hBrush;
		switch (iPaintFlag) {

		case 1 :
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 2 :
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 5:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 6 :
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 7 :
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 8:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 9:
			hBrush = CreateSolidBrush(RGB(64, 64, 64));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 10 :
			hBrush = CreateSolidBrush(RGB(124, 124, 124));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

		case 11:
			hBrush = CreateSolidBrush(RGB(192, 192, 192));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		}

		EndPaint(hwnd, &ps);
		break;
	}

	
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}