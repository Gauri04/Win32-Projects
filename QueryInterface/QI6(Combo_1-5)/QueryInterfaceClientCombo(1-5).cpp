//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

// ***************** Code For All Query Interfaces's Properties : Identity, Predictability, *************************
//							** Symmetry, Reflexivity, and Transitivity **

#include <windows.h>
#include"ClassFactoryDllServerWithRegFile.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;



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
	
	IUnknown *pIUnknownFromISum = NULL;
	IUnknown *pIUnknownFromISubtract = NULL;
	IMultiply *pIMultiply = NULL;
	HRESULT hr;
	TCHAR str[255];

	BOOL Identity(ISum *, ISubtract *);
	BOOL Predictability(ISum *);
	BOOL Symmetry(ISum *);
	BOOL Reflexivity(ISum *);
	BOOL Transitivity(ISum *);
	BOOL isSuccess;


	switch (iMsg)
	{

	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum interface cannot be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 5;
		iNum2 = 5;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Sum Of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}


		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Subtraction Of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);


		hr = pISubtract->QueryInterface(IID_IMultiply, (void **)&pIMultiply);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IMultiply interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIMultiply->MultiplicationOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Multiplication Of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		//QI first property: Identity
		isSuccess = Identity(pISum, pISubtract);
		if (isSuccess) {
			MessageBox(NULL, TEXT("Identity in COM is proved; (Diamond Problem)"), TEXT("Identity"), MB_OK);
		}
		else {
			MessageBox(hwnd, TEXT("Identity not proved (Diamond Problem)"), TEXT("Identity"), MB_OK);
		}

		// QI second property : Predictability
		isSuccess = Predictability(pISum);
		if (isSuccess) {
			MessageBox(hwnd, TEXT("Predictability Proved!!"), TEXT("Predictability"), MB_OK);
		}
		else {
			MessageBox(hwnd, TEXT("Predictability not Proved!!"), TEXT("Predictability"), MB_OK);
		}

		// QI third property : Symmetry
		isSuccess = Symmetry(pISum);
		if (isSuccess) {
			MessageBox(hwnd, TEXT("Symmetry Proved!!"), TEXT("Symmetry"), MB_OK);
		}
		else {
			MessageBox(hwnd, TEXT("Symmetry not Proved!!"), TEXT("Symmetry"), MB_OK);
		}

		// QI fourth property : Reflexivity
		isSuccess = Reflexivity(pISum);
		if (isSuccess) {
			MessageBox(hwnd, TEXT("Reflexivity Proved!!"), TEXT("Reflexivity"), MB_OK);
		}
		else {
			MessageBox(hwnd, TEXT("Reflexivity not Proved!!"), TEXT("Reflexivity"), MB_OK);
		}

		// QI fifth property : Transitivity
		isSuccess = Transitivity(pISum);
		if (isSuccess) {
			MessageBox(hwnd, TEXT("Transitivity Proved!!"), TEXT("Transitivity"), MB_OK);
		}
		else {
			MessageBox(hwnd, TEXT("Transitivity not Proved!!"), TEXT("Transitivity"), MB_OK);
		}


		pIMultiply->Release();
		pIMultiply = NULL;

		pISubtract->Release();
		pISubtract = NULL;

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

BOOL Identity(ISum *pISum, ISubtract *pISubtract ) {
	HRESULT hr;
	BOOL flag;
	ISum *pIUnknownFromISum, *pIUnknownFromISubtract;

	hr = pISum->QueryInterface(IID_IUnknown, (void **)&pIUnknownFromISum);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IUnknown interface from iSum cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	hr = pISubtract->QueryInterface(IID_IUnknown, (void **)&pIUnknownFromISubtract);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IUnknown interface drom iSubtract cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	if (pIUnknownFromISum == pIUnknownFromISubtract) {
		flag = TRUE;
	}
	else {
		flag = FALSE;
	}
	pIUnknownFromISubtract->Release();
	pIUnknownFromISubtract = NULL;

	pIUnknownFromISum->Release();
	pIUnknownFromISum = NULL;

	return flag;

}

BOOL Predictability(ISum * pISum) {
	HRESULT hr;
	int iNum1 = 50;
	int iNum2 = 10;
	int iNum3 = NULL;
	TCHAR str[255];

	hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}


	pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
	wsprintf(str, TEXT("Subtraction Of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("Result"), MB_OK);

	pISubtract->Release();
	pISubtract = NULL;

	Sleep(5000);

	hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("pISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
	if (pISubtract == NULL) {
		return FALSE;
	}
	wsprintf(str, TEXT("Subtraction of two integers %d and %d is : %d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("Result"), MB_OK);
	MessageBox(NULL,
		TEXT("As pISubtract gets called after 5 seconds, even after releasing it,predictability is proved"),
		TEXT("INFO"), MB_OK);

	pISubtract->Release();
	pISubtract = NULL;
	pISum->Release();

	return TRUE;
}


BOOL Symmetry(ISum *pISum) {
	HRESULT hr;
	BOOL flag;
	ISubtract *pISubtract = NULL;
	ISum *pISumAgain = NULL;
	int iNum1 = 10, iNum2 = 5, iNum3 = NULL;
	TCHAR str[255];

	hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}


	pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
	wsprintf(str, TEXT("Subtraction of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("RESULT"), MB_OK);


	hr = pISubtract->QueryInterface(IID_ISum, (void **)&pISumAgain);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ISum interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	pISumAgain->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
	wsprintf(str, TEXT("Sum of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("RESULT"), MB_OK);

	if (pISum == pISumAgain) {
		MessageBox(NULL, TEXT("pISum and pISumAgain are same. Hence proved symmetry"), TEXT("Result"), MB_OK);
		flag = TRUE;
	}
	else {
		MessageBox(NULL, TEXT("pISum and pISumAgain are not same.Symmetry not proved"), TEXT("Result"), MB_OK);
		flag = FALSE;
	}

	pISumAgain->Release();
	pISumAgain = NULL;

	pISubtract->Release();
	pISubtract = NULL;

	pISum -> Release();
	return flag;
}

BOOL Reflexivity(ISum *pISum) {
	HRESULT hr;
	BOOL flag;
	ISum *pISumFromISum;
	int iNum1 = 10, iNum2 = 5, iNum3 = NULL;
	TCHAR str[255];

	hr = pISum->QueryInterface(IID_ISum, (void **)&pISumFromISum);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ISum interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	pISumFromISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
	wsprintf(str, TEXT("Sum of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("RESULT"), MB_OK);

	if (pISum == pISumFromISum){
		MessageBox(NULL, TEXT("pISumFromISum gets called from ISum. Hence proved reflexivity"), TEXT("RESULT"), MB_OK);
		flag = TRUE;
	}
	else{
		MessageBox(NULL, TEXT("Reflexivity not proved"), TEXT("ERROR!"), MB_OK);
		flag = FALSE;
	}
	pISumFromISum->Release();
	pISumFromISum = NULL;
	return flag;
}

BOOL Transitivity(ISum *pISum) {
	HRESULT hr;
	BOOL flag;
	ISubtract *pISubtract = NULL;
	IMultiply *pIMultiply = NULL;
	ISum *pISumFromIMultiply = NULL;
	int iNum1 = 10, iNum2 = 5, iNum3 = NULL;
	TCHAR str[255];


	hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
	wsprintf(str, TEXT("Subtraction of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("RESULT"), MB_OK);

	hr = pISubtract->QueryInterface(IID_IMultiply, (void **)&pIMultiply);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IMultiply interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	pIMultiply->MultiplicationOfTwoIntegers(iNum1, iNum2, &iNum3);
	wsprintf(str, TEXT("Multiplication of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("RESULT"), MB_OK);



	hr = pIMultiply->QueryInterface(IID_ISum, (void **)&pISumFromIMultiply);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ISum interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
	}

	pISumFromIMultiply->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
	if (pISumFromIMultiply == NULL) {
		flag = FALSE;
	}
	else {
		flag = TRUE;
	}
	wsprintf(str, TEXT("Sum of two integers %d and %d is :%d"), iNum1, iNum2, iNum3);
	MessageBox(NULL, str, TEXT("RESULT"), MB_OK);
	MessageBox(NULL,
		TEXT("ISum can be called from pIMultiply. pIMultiply from->pISubtract. pISubtract from ISum. Hence transitivity proved"),
		TEXT("Result"), MB_OK);

	pISumFromIMultiply->Release();
	pISumFromIMultiply = NULL;
	return flag;
}