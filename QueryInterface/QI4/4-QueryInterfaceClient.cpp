//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64
// ***************** Code For Query Interfaces's Fourth Property : Reflexivity *************************
//         ****** Here we will call pISum from ISum in order to prove reflexiviy **********

#include <windows.h>
#include "ClassFactoryDllServerWithRegFile.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ClientClassFactoryDllServerWithRegFile");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Error initializing COM library"), TEXT("ERROR!"), MB_OK);
		exit(0);
	}


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
		TEXT("ClientClassFactoryDllServerWithRegFile"),
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
	CoUninitialize();
	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	ISum *pISum;
	ISubtract *pIsubtract;
	ISum *pISumFromISum;
	HRESULT hr;
	int iNum1, iNum2, iNum3;
	TCHAR str[255];

	// Function Declaration
	void SafeInterfaceRelease(void);

	switch (iMsg)
	{

	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 45;
		iNum2 = 55;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Sum of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pIsubtract);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIsubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Subtraction of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISum, (void **)&pISumFromISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISumFromISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Sum of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		if (pISum == pISumFromISum)
			MessageBox(hwnd, TEXT("pISumFromISum gets called from ISum. Hence proved reflexivity"), TEXT("RESULT"), MB_OK);
		else
			MessageBox(hwnd, TEXT("Reflexivity not proved"), TEXT("ERROR!"), MB_OK);

		pISumFromISum->Release();
		pISumFromISum = NULL;

		pIsubtract->Release();
		pIsubtract = NULL;

		pISum->Release();
		pISum = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

