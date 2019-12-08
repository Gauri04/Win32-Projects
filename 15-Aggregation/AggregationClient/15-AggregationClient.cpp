//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <windows.h>
#include "aggregationComboHeader.h"


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
	IMultiplication *pIMultiply;
	IDivision *pIDivision;
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

		iNum1 = 10;
		iNum2 = 5;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Sum of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pIsubtract);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISum->Release();
		pISum = NULL;

		pIsubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Subtraction of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pIsubtract->QueryInterface(IID_IMultiplication, (void **)&pIMultiply);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IMultiply interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIsubtract->Release();
		pIsubtract = NULL;

		pIMultiply->MultiplicationOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Multiplication of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pIMultiply->QueryInterface(IID_IDivision, (void **)&pIDivision);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IDivision interface cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIMultiply->Release();
		pIMultiply = NULL;

		pIDivision->DivisionOfTwonIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Division of two integers %d and %d is: %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		pIDivision->Release();
		pIDivision = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
