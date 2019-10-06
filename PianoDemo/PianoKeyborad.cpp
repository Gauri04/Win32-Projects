//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <windows.h>
#include<mmsystem.h>
#include "PianoHeader.h"
# define MYTIMER 200
#define MYTIMER2 202


#pragma comment(lib, "winmm.lib")

void PlayBdaySong(void);
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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Piano"),
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
	static RECT rcTemp;
	static RECT rcTemp2;
	static int iKeyFlag = 0;
	static int iSoundScales = 0;
	static int iTimerFlag = 0;
	static HBITMAP hBitmap = NULL;
	static HBITMAP hBitmap2 = NULL;
	TCHAR str1[] = TEXT("Press 'c' for C notes");
	TCHAR str2[] = TEXT("Press 'd' for F notes");
	TCHAR str3[] = TEXT("Press 'f' for C# notes");
	TCHAR str4[] = TEXT("Press 'o' for returning from the notes");
	TCHAR str5[] = TEXT("Press 'z' for");


	switch (iMsg)
	{
		static long lRCRight;
		static long lRCRight2;
		HBRUSH hBrush;
		HBRUSH hWhiteBrush;

	case WM_CREATE:
		hInstance = GetModuleHandle(NULL);
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BIRTHDAYBITMAP));
		hBitmap2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(PIANOBITMAP));
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		switch (LOWORD(wParam)) {

		case 'c':
		case 'C':
			iSoundScales = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'd':
		case 'D':
			iSoundScales = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'f':
		case 'F':
			iSoundScales = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'O':
		case 'o':
			iSoundScales = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'z':
		case 'Z':
			iSoundScales = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			PlayBdaySong();
			SetTimer(hwnd, MYTIMER, 100, NULL);
			break;

		case '1':
			iKeyFlag = 1;
			// tried using sndPlaySound()
			// sndPlaySound(TEXT("c5.wav"), SND_ASYNC);

			if (iSoundScales == 1) {
				PlaySound(TEXT("C(Sa).wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (iSoundScales == 2) {
				PlaySound(TEXT("d(Sa).wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (iSoundScales == 3) {
				PlaySound(TEXT("cs(Sa).wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case '2':
			iKeyFlag = 2;
			if (iSoundScales == 1)
				PlaySound(TEXT("C(Re).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 2)
				PlaySound(TEXT("d(Re).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 3)
				PlaySound(TEXT("cs(Re).wav"), NULL, SND_FILENAME | SND_ASYNC);
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case '3':
			iKeyFlag = 3;
			if (iSoundScales == 1)
				PlaySound(TEXT("C(Ga).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 2)
				PlaySound(TEXT("d(Ga).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 3)
				PlaySound(TEXT("cs(Ga).wav"), NULL, SND_FILENAME | SND_ASYNC);
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case '4':
			iKeyFlag = 4;
			if (iSoundScales == 1)
				PlaySound(TEXT("C(Ma).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 2)
				PlaySound(TEXT("d(Ma).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 3)
				PlaySound(TEXT("cs(Ma).wav"), NULL, SND_FILENAME | SND_ASYNC);
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case '5':
			iKeyFlag = 5;
			if (iSoundScales == 1)
				PlaySound(TEXT("C(Pa).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 2)
				PlaySound(TEXT("d(Pa).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 3)
				PlaySound(TEXT("cs(Pa).wav"), NULL, SND_FILENAME | SND_ASYNC);
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case '6':
			iKeyFlag = 6;
			if (iSoundScales == 1)
				PlaySound(TEXT("C(Dha).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 2)
				PlaySound(TEXT("d(Dha).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 3)
				PlaySound(TEXT("cs(Dha).wav"), NULL, SND_FILENAME | SND_ASYNC);
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case '7':
			iKeyFlag = 7;
			if (iSoundScales == 1)
				PlaySound(TEXT("C(Ni).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 2)
				PlaySound(TEXT("d(Ni).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 3)
				PlaySound(TEXT("cs(Ni).wav"), NULL, SND_FILENAME | SND_ASYNC);
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case '8':
			iKeyFlag = 8;
			if (iSoundScales == 1)
				PlaySound(TEXT("C(SA2).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 2)
				PlaySound(TEXT("d(Sa2).wav"), NULL, SND_FILENAME | SND_ASYNC);
			else if (iSoundScales == 3)
				PlaySound(TEXT("cs(Sa2).wav"), NULL, SND_FILENAME | SND_ASYNC);
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		}
		break;

		case WM_TIMER:
			iTimerFlag = iTimerFlag + 4;
			if (iTimerFlag == 780) {
				KillTimer(hwnd, MYTIMER);
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;


	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));


		// Set First Window (Splash Screen)
		if (iSoundScales == 0) {
			BITMAP bitmap2;
			iTimerFlag = 0;

			FillRect(hdc, &rc, hBrush);
			if (hBitmap2 == NULL) {
				MessageBox(hwnd, TEXT("Could Not Load Bitmap!!"), TEXT("Error!"), MB_OK);
			}

			HDC memoryHdc2 = CreateCompatibleDC(NULL);
			SelectObject(memoryHdc2, hBitmap2);
			FillRect(hdc, &rc, hBrush);
			GetObject(hBitmap2, sizeof(bitmap2), &bitmap2);
			StretchBlt(hdc,
				(rc.right / 2) - 250,
				rc.top + 30,
				bitmap2.bmWidth,
				bitmap2.bmHeight,
				memoryHdc2,
				0,
				0,
				bitmap2.bmWidth,
				bitmap2.bmHeight,
				SRCCOPY);

			DeleteDC(memoryHdc2);

			
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, rc.right / 2 - 80, rc.bottom / 2 - 20, str1, lstrlen(str1));
			TextOut(hdc, rc.right / 2 - 80, rc.bottom / 2 + 20, str2, lstrlen(str2));
			TextOut(hdc, rc.right / 2 - 80, rc.bottom / 2 + 60, str3, lstrlen(str3));
			TextOut(hdc, rc.right / 2 - 120, rc.bottom / 2 + 100, str4, lstrlen(str4));
			TextOut(hdc, rc.right / 2 - 55, rc.bottom / 2 + 140, str5, lstrlen(str5)); 
			
		}

		else if (iSoundScales == 4) {

			BITMAP bitmap;

			if (hBitmap == NULL) {
				MessageBox(hwnd, TEXT("Could Not Load Bitmap!!"), TEXT("Error!"), MB_OK);
			}
			HDC memoryHdc = CreateCompatibleDC(NULL);
			SelectObject(memoryHdc, hBitmap);
			FillRect(hdc, &rc, hBrush);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			StretchBlt(hdc,
				-250 + iTimerFlag,
				150,
				bitmap.bmWidth,
				bitmap.bmHeight,
				memoryHdc,
				0,
				0,
				bitmap.bmWidth,
				bitmap.bmHeight,
				SRCCOPY);

			DeleteDC(memoryHdc);
		}



		else {
			lRCRight = rc.right / 8;


			// For black lines that divides the piano tiles
			for (int i = 1; i <= 7; i++) {
				rcTemp.left = (lRCRight * i) - 10;
				rcTemp.right = lRCRight * i;
				rcTemp.top = rc.top;
				rcTemp.bottom = rc.bottom;
				FillRect(hdc, &rcTemp, hBrush);
			}

			// For black piano tiles: left
			for (int i = 1; i <= 7; i++) {
				if (i == 1 || i == 2 || i == 4 || i == 5 || i == 6) {
					rcTemp.left = (lRCRight * i) - 30;
					rcTemp.right = lRCRight * i;
					rcTemp.top = rc.top;
					rcTemp.bottom = rc.bottom / 2.5;
					FillRect(hdc, &rcTemp, hBrush);
				}

			}

			// For black piano tiles: right
			for (int i = 1; i <= 7; i++) {
				if (i == 1 || i == 2 || i == 4 || i == 5 || i == 6) {
					rcTemp.left = (lRCRight * i) + 20;
					rcTemp.right = lRCRight * i;
					rcTemp.top = rc.top;
					rcTemp.bottom = rc.bottom / 2.5;
					FillRect(hdc, &rcTemp, hBrush);
				}
			}

			// For lower black coloured border
			rcTemp.top = rc.bottom - 10;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = rc.left;
			rcTemp.right = rc.right;
			FillRect(hdc, &rcTemp, hBrush);

			// For upper black coloured border
			rcTemp.top = rc.top;
			rcTemp.bottom = rcTemp.top + 10;
			FillRect(hdc, &rcTemp, hBrush);

			// For left black colored border
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = rc.left;
			rcTemp.right = rc.left + 10;
			FillRect(hdc, &rcTemp, hBrush);

			// For right black coloured border
			rcTemp.left = rc.right - 10;
			rcTemp.right = rc.right;
			FillRect(hdc, &rcTemp, hBrush);

			// if Key 1 is pressed, highlight first piano tile 
			if (iKeyFlag == 1) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = rc.left;
				rcTemp.right = lRCRight;
				FillRect(hdc, &rcTemp, hBrush);
			}
			// if Key 2 is pressed
			if (iKeyFlag == 2) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = lRCRight;
				rcTemp.right = lRCRight * 2;
				FillRect(hdc, &rcTemp, hBrush);
			}

			if (iKeyFlag == 3) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = lRCRight * 2;
				rcTemp.right = lRCRight * 3;
				FillRect(hdc, &rcTemp, hBrush);
			}

			if (iKeyFlag == 4) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = lRCRight * 3;
				rcTemp.right = lRCRight * 4;
				FillRect(hdc, &rcTemp, hBrush);
			}

			if (iKeyFlag == 5) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = lRCRight * 4;
				rcTemp.right = lRCRight * 5;
				FillRect(hdc, &rcTemp, hBrush);
			}

			if (iKeyFlag == 6) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = lRCRight * 5;
				rcTemp.right = lRCRight * 6;
				FillRect(hdc, &rcTemp, hBrush);
			}

			if (iKeyFlag == 7) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = lRCRight * 6;
				rcTemp.right = lRCRight * 7;
				FillRect(hdc, &rcTemp, hBrush);
			}

			if (iKeyFlag == 8) {
				rcTemp.top = rc.bottom - 30;
				rcTemp.bottom = rc.bottom;
				rcTemp.left = lRCRight * 7;
				rcTemp.right = lRCRight * 8;
				FillRect(hdc, &rcTemp, hBrush);
			}
		}

		break;




	}


	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
void PlayBdaySong(void) {
	PlaySound(TEXT("bday.wav"), NULL, SND_FILENAME | SND_ASYNC);
}










