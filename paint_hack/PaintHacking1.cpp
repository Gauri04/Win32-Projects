#include<windows.h>
#include"PaintIconHeader.h"
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define MYTIMER1 1001


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumWindowsProc(HWND, LPARAM lParam);

static HWND hwndPaint = 0;
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("PaintHacking");

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

	EnumWindows(EnumWindowsProc, NULL);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("My Paint Hack app"),
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

	TCHAR str[] = TEXT("Press 'k' to close Paint Window");
	static HDC hdc;
	static RECT rc;
	BOOL fPaintHandle;
	static HBRUSH hBrushRed = NULL;
	static HBRUSH hBrushBlue = NULL;
	static HBRUSH hBrushGreen = NULL;
	static BOOL isDraw = FALSE;
	static POINT ptPrevious;
	static RECT rcTemp;
	static HDC hdcPaint;
	static int i = 0;
	static BOOL isTimer = FALSE;
	static HICON hIconPaint = NULL;
	static int timerFrom = 0;

	switch (iMsg) {
	case WM_DESTROY:
		ReleaseDC(hwndPaint, hdcPaint);
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		//Get handle of paint window
		fPaintHandle = EnumWindows(EnumWindowsProc, NULL);
		if (hwndPaint == NULL) {
			MessageBox(hwnd, TEXT("Cannot get handle to paint"), TEXT("Error"), MB_OK);
			PostQuitMessage(0);
		}
		//get hdc of paint
		hdcPaint = GetDC(hwndPaint);
		// load icon which will be used to set to paint window
		hIconPaint = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(MYICON));
		hdc = GetDC(hwnd);
		//brush to fill rectangle with rgb colors on paint window
		hBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
		hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
		hBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
		
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, ((rc.right / 2) - 50), 30, str, lstrlen(str));
		TextOut(hdc, ((rc.right / 2) - 50), 50, TEXT("Press spacebar to display rectangle"), 35);
		TextOut(hdc, ((rc.right / 2) - 50), 70, TEXT("Press I to change paint icon"), 32);
		TextOut(hdc, ((rc.right / 2) - 50), 90, TEXT("Press T to draw triangle"), 29);
		break;


	case WM_LBUTTONDOWN:
		isDraw = TRUE;
		//this code referred from msdn
		ptPrevious.x = LOWORD(lParam);
		ptPrevious.y = HIWORD(lParam);

	case WM_MOUSEMOVE:
		// code referred from msdn (draw line on paint using mouse co-ordinates)
		if (isDraw) {
			MoveToEx(hdcPaint, ptPrevious.x, ptPrevious.y, NULL);
			LineTo(hdcPaint, ptPrevious.x = LOWORD(lParam), ptPrevious.y = HIWORD(lParam));
		}
		break;

	case WM_LBUTTONUP:
		// code referred from msdn
		if (isDraw) {
			MoveToEx(hdcPaint, ptPrevious.x, ptPrevious.y, NULL);
			LineTo(hdcPaint, LOWORD(lParam), HIWORD(lParam));
		}
		// stop when mouse key up (LButtonUp) pressed
		isDraw = FALSE;
		break;


	case WM_CHAR:
		switch (LOWORD(wParam)) {
		case 'k':
		case 'K':
			// k to close paint window
			MessageBox(hwndPaint, TEXT("Closing Paint"), TEXT("INFO"), MB_OK);
			SendMessage(hwndPaint, WM_CLOSE, NULL, NULL);

		case VK_SPACE:
			// reset timer if already used
			isTimer = FALSE;
			// used one timer for two cases (VK_SPACE and case 'T'). so used timerfrom to identify
			// from which case it is being used 
			timerFrom = 1;
			// used i for incrementation(incremented in case TIMER)
			i = 0;
			if (!isTimer) {
				SetTimer(hwnd, MYTIMER1, 1000, NULL);
			}
			break;
			
		case 'i':
		case 'I':
			// sets the icon to paint window
			SendMessage(hwndPaint, WM_SETICON, 0, (LPARAM)hIconPaint);
			break;

		case 't':
		case 'T':
			// identifies the timer is from case 't'
			timerFrom = 2;
			i = 1;
			// play sound while drawing triangle on paint window 
			PlaySound(TEXT("Tokyo_Drift_Paint.wav"), NULL, SND_FILENAME | SND_ASYNC);
			SetTimer(hwnd, MYTIMER1, 1000, NULL);
			break;
		}
		break;

	case WM_TIMER:
		isTimer = TRUE;
		KillTimer(hwnd, MYTIMER1);
		if (timerFrom == 1) {
			// draw rectangle on paint window
			if (i <= 150) {
				i = i + 1;
				rcTemp.left = 200;
				rcTemp.top = 300;
				rcTemp.right = 200 + i;
				rcTemp.bottom = 300 + i;
				// fill the small part of rectangle using red color
				if (i < 70) {
					FillRect(hdcPaint, &rcTemp, hBrushRed);
				}
				// fill next part of rectangle using green
				else if (i < 100) {
					FillRect(hdcPaint, &rcTemp, hBrushGreen);
				}
				// fill remaining rectangle using blue color
				else {
					FillRect(hdcPaint, &rcTemp, hBrushBlue);
				}
				
				SetTimer(hwnd, MYTIMER1, 100, NULL);
			}
			else {
				KillTimer(hwnd, MYTIMER1);
			}
		}
		else if (timerFrom == 2) {
			// move the line upto 150 points
			if (i < 150) {
				
				MoveToEx(hdcPaint, 200 - i, 300 + i, NULL);
				LineTo(hdcPaint, 200 - i - 1, 300 + i + 1);

				
				MoveToEx(hdcPaint, 200 + i, 300 + i, NULL);
				LineTo(hdcPaint, 200 + i + 1, 300 + i + 1);

				MoveToEx(hdcPaint, 49 + i, 451, NULL);
				LineTo(hdcPaint, 50 + (i*2) + 1, 451);
				i++;
				SetTimer(hwnd, MYTIMER1, 100, NULL);	
			}
			else {
				KillTimer(hwnd, MYTIMER1);
			}
		
		}
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	char class_name[500] = { NULL };
	char title[80] = { NULL };;
	GetClassNameA(hwnd, class_name, sizeof(class_name));
	GetWindowTextA(hwnd, title, sizeof(title));
	// get hwnd only if it is paint window (class name is paint)
	if (strcmp(class_name, "MSPaintApp") == 0) {
		hwndPaint = hwnd;
		return(FALSE);
	}
	return(TRUE);
	
}























