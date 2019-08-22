#include <windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);

DWORD WINAPI ThreadProcTwo(LPVOID);

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
		TEXT("MY_FIRST_MULTITHREAD_PROGRAM"),
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;

	switch (iMsg) {
	case WM_CREATE:

		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne,
			(LPVOID)hwnd, 0, NULL);

		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo,
			(LPVOID)hwnd, 0, NULL);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Left Mouse Clicked"), TEXT("Message"), MB_OK);
		break;

	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {
	HDC hdc;
	long i;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 0; i < 4294967295; i++) {
		wsprintf(str, TEXT("Thread One -> Increasing Order: %ld"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return(0);

}

DWORD WINAPI ThreadProcTwo(LPVOID param) {
	HDC hdc;
	long j;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	//MessageBox((HWND)param, TEXT("test function 2"), TEXT("ThreadProc2"), MB_OK);
	for (j = 429496729; j > 0; j--) {
		wsprintf(str, TEXT("Thread Two -> Decreasing Order: %ld"), j);
		TextOut(hdc, 5, 20, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return(0);

}












