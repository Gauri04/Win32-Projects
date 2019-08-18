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
		TEXT("DLL Using Visual Studio (DelcSpec Implicit)"),
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
	int i, j;
	wchar_t str[255];
	typedef int(*makeSquareFnPtr)(int);
	makeSquareFnPtr pfn = NULL;
	HINSTANCE hDll = NULL;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		i = 25;
		// Load library from DLL
		hDll = LoadLibrary(TEXT("B-Def.dll"));
		if (hDll == NULL) {
			MessageBox(hwnd, TEXT("Cannot load library"), TEXT("Error- Library"), MB_OK);
			DestroyWindow(hwnd);
		}
		pfn = (makeSquareFnPtr)GetProcAddress(hDll, "MakeSquare");
		if (pfn == NULL) {
			MessageBox(hwnd, TEXT("Cannot get function from library"), TEXT("Error- Function Pointer"), MB_OK);
			DestroyWindow(hwnd);
		}

		j = pfn(i);
		wsprintf(str, TEXT("Square of %d is = %d"), i, j);
		MessageBox(hwnd, str, TEXT("Square"), iMsg);
		FreeLibrary(hDll);
		DestroyWindow(hwnd);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}



