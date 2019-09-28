//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <windows.h>
#include<mmsystem.h>
#include"resource.h"
#pragma comment(lib, "winmm.lib")


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
	static HINSTANCE hInstance;
	static int iKeyFlag = 0;
	HANDLE handleA;
	switch (iMsg)
	{

	case WM_CREATE:
		hInstance = GetModuleHandle(NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		switch (LOWORD(wParam)) {
		case '1':
			iKeyFlag = 1;
			// tried using sndPlaySound()
			// sndPlaySound(TEXT("c5.wav"), SND_ASYNC);
			PlaySound(TEXT("c5.wav"), NULL, SND_FILENAME | SND_NOWAIT | SND_ASYNC);
			break;

		case '2':
			iKeyFlag = 2;
			// tried using sndPlaySound()
			//sndPlaySound(TEXT("d5.wav"), SND_ASYNC);
			PlaySound(TEXT("d5.wav"), NULL, SND_FILENAME | SND_NOWAIT | SND_ASYNC);
			break;

		case '3':
			//sndPlaySound(TEXT("e5.wav"), SND_ASYNC);
			PlaySound(TEXT("e5"), NULL, SND_FILENAME | SND_NOWAIT | SND_ASYNC);
			break;

		case '4':
			//sndPlaySound(TEXT("f5.wav"), SND_ASYNC);
			PlaySound(TEXT("f5"),NULL, SND_FILENAME | SND_ASYNC);
			break;

		case '5':
			//sndPlaySound(TEXT("g5.wav"), SND_ASYNC);
			PlaySound(TEXT("g5"), NULL, SND_FILENAME | SND_ASYNC);
			break;

		case '6':
			iKeyFlag = 6;
			//sndPlaySound(TEXT("a5.wav"), SND_ASYNC);
			PlaySound(TEXT("a5"), NULL, SND_FILENAME | SND_ASYNC);
			break;

		case '7':
			iKeyFlag = 7;
			//sndPlaySound(TEXT("b5.wav"), SND_ASYNC);
			PlaySound(TEXT("b5"), NULL, SND_FILENAME | SND_ASYNC);
			break;

		case '8':
			iKeyFlag = 8;
			//sndPlaySound(TEXT("postc6.wav"), SND_SYNC);
			PlaySound(TEXT("post c6"), NULL, SND_FILENAME | SND_ASYNC);
			break;		
		}
		break;

	case WM_KEYUP:
		
		break;

	
	}


	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}