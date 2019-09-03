//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <windows.h>
#define MYTIMER 101


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
		TEXT("Timer"),
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
	static RECT rcTemp;
	static int iFlag = 0;
	PAINTSTRUCT ps;
	static long lRCRight = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, MYTIMER, 2000, NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MYTIMER);
		if (iFlag > 8) {
			iFlag = 0;
		}
		iFlag = iFlag + 1;
		
		InvalidateRect(hwnd, NULL, true);
		SetTimer(hwnd, MYTIMER, 2000, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		// initialize top and bottom coordinates of window to be painted
		rcTemp.bottom = rc.bottom;
		rcTemp.top = rc.top;

		// define width of the rectangle to be painted 
		 lRCRight = rc.right / 8;
		
		HBRUSH hBrush;


		switch (iFlag) {

		case 8:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			rcTemp.left = lRCRight * 7;
			rcTemp.right = lRCRight * 8;
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);

		case 7:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			rcTemp.left = lRCRight * 6;
			rcTemp.right = lRCRight * 7;
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);


		case 6:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			rcTemp.left = lRCRight * 5;
			rcTemp.right = lRCRight * 6;
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
		
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			rcTemp.left = lRCRight * 4;
			rcTemp.right = lRCRight * 5;
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);


		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			rcTemp.left = lRCRight * 3;
			rcTemp.right = lRCRight * 4;
			FillRect(hdc, &rcTemp, hBrush);


		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			rcTemp.left = lRCRight * 2;
			rcTemp.right = lRCRight * 3;
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);

		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			rcTemp.left = lRCRight;
			rcTemp.right = lRCRight * 2;
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);

		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			rcTemp.left = 0;
			rcTemp.right =  lRCRight;
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

