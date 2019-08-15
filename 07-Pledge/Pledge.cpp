//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <windows.h>
#include<stdio.h>



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
		TEXT("प्रतिज्ञा"),
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
	TEXTMETRIC tm;
	static int cyChar;
	RECT rc;
	int i, X, Y;
	PAINTSTRUCT ps;
	LPCWSTR str[] = { TEXT("India is my country and all Indians are my brothers and sisters."),
		TEXT("I love my country and I am proud of its rich and varied heritage. I shall always strive to be worthy of it."),
		TEXT("\n"),
		TEXT("I shall give respect to my parents, teachers and elders and treat everyone with courtesy."),
		TEXT("\n"),
		TEXT("To my country and my people, I pledge my devotion. In their well being and prosperity alone, lies my happiness."),
		TEXT("\n"),
		TEXT("Jai Hind") };

	LPCWSTR strMarathi[] = { TEXT("भारत माझा देश आहे. सारे भारतीय माझे बांधव आहेत."),
		TEXT("\n"),
		TEXT("माझ्या देशावर माझे प्रेम आहे."),
		TEXT("माझ्या देशातल्या समृद्ध आणि विविधतेने नटलेल्या परंपरांचा मला अभिमान आहे. त्या परंपरांचा पाईक होण्याची पात्रता माझ्या अंगी यावी म्हणून मी सदैव प्रयत्न करेन."),
		TEXT("\n"),
		TEXT("मी माझ्या पालकांचा, गुरुजनांचा आणि वडीलधा-या माणसांचा मान ठेवेन आणि प्रत्येकाशी सौजन्याने वागेन."),
		TEXT("\n"),
		TEXT("माझा देश आणि माझे देशबांधव यांच्याशी निष्ठा राखण्याची मी प्रतिज्ञा करीत आहे.") ,
		TEXT("\n"),
		TEXT("त्यांचे कल्याण आणि त्यांची समृद्धी ह्यांतच माझे सौख्य सामावले आहे."),
		TEXT("\n"),
		TEXT("जय हिंद !!!") };

	switch (iMsg)
	{
		
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 165, 0));
		X = 50;
		Y = 5;
				
		for (i = 0; i <= 7; ++i) {
			TextOut(hdc, X, Y, str[i], lstrlen(str[i]));
			Y = Y + cyChar;
		}

		SetTextColor(hdc, RGB(255, 255, 255));
		Y = 200;
		X = 50;
		for (i = 0; i <= 11; ++i) {

			TextOut(hdc, X, Y, strMarathi[i], lstrlen(strMarathi[i]));
			Y = Y + cyChar;
		}


		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

