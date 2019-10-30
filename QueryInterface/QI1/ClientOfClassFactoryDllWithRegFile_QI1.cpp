//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

// ***************** Code For Query Interfaces's First Property : Identity *************************
// ** Here we will get two pointers IUnknownFromISum and pIUnknownFromISubtract and prove that they both are same **

#include <windows.h>
#include"ClassFactoryDllServerWithRegFile.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ClientOfClassFactoryDllServerWithRegFile_QI1");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
		MessageBox(NULL, TEXT("COM initialization failed"), TEXT("ERROR!"), MB_OK);


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
		TEXT("ClientOfClassFactoryDllServerWithRegFile_QI1"),
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
	int iNum1, iNum2, iNum3;
	ISum *pISum = NULL;
	IUnknown *pIUnknownFromISum = NULL;
	IUnknown *pIUnknownFromISubtract = NULL;
	ISubtract *pISubtract = NULL;
	IMultiply *pIMultiply = NULL;
	HRESULT hr;
	TCHAR str[255];

	switch (iMsg)
	{
	
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 5;
		iNum2 = 5;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Subtraction Of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pISubtract->QueryInterface(IID_ISum, (void **)&pISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}


		pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Sum Of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);


		hr = pISubtract->QueryInterface(IID_IMultiply, (void **)&pIMultiply);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IMultiply interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pISum->QueryInterface(IID_IUnknown, (void **)&pIUnknownFromISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IUnknown interface from iSum cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pISubtract->QueryInterface(IID_IUnknown, (void **)&pIUnknownFromISubtract);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IUnknown interface drom iSubtract cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		if (pIUnknownFromISum == pIUnknownFromISubtract) {
			MessageBox(hwnd, TEXT("Identity in COM is proved; (Diamond Problem)"), TEXT("Identity"), MB_OK);
		}
		else
			MessageBox(hwnd, TEXT("Identity not same (Diamond Problem)"), TEXT("Identity"), MB_OK);

		pIUnknownFromISubtract->Release();
		pIUnknownFromISubtract = NULL;

		pIUnknownFromISum->Release();
		pIUnknownFromISum = NULL;

		pISum->Release();
		pISum = NULL;

		pISubtract->Release();
		pISubtract = NULL;


		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

