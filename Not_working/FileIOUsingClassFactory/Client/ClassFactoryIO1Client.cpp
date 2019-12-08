//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <windows.h>
#include<fstream>
#include "ClassFactoryDllServerWithRegFile.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ClassFactoryFileIO1Client");
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
		TEXT("Class Factory File IO 1 Client"),
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
	IReadRecordFile *pIReadRecordFile = NULL;
	IWriteRecordFile *pIWriteRecordFile = NULL;
	
	HRESULT hr;
	char str[255];
	char *ptr[255];
	char input[5][200] = { "Seema", "20", "3", "1"};;
	char readBuffer[4][200];

	// Function Declaration
	void SafeInterfaceRelease(void);

	switch (iMsg)
	{

	case WM_CREATE:
		hr = CoCreateInstance(CLSID_CRecordFile, NULL, CLSCTX_INPROC_SERVER, IID_IWriteRecordFile, (void **)&pIWriteRecordFile);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IReadRecordFile interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		pIWriteRecordFile->WriteRecord(input);
		//	wsprintf(str, TEXT("File write complete"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, TEXT("File write successful"), TEXT("RESULT"), MB_OK);

		hr = pIWriteRecordFile->QueryInterface(IID_IReadRecordFile, (void **)&pIReadRecordFile);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IReadRecord interface cannot be obtained"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIWriteRecordFile->Release();
		pIWriteRecordFile = NULL;
		

		hr = pIReadRecordFile->ReadRecord((char **)&readBuffer);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Error reading file"), TEXT("ERROR!"), MB_OK);
			DestroyWindow(hwnd);
		}
		//wsprintf(str, TEXT("%s"),readBuffer);
		MessageBox(hwnd, (LPCWSTR)readBuffer, TEXT("RESULT"), MB_OK);

		pIReadRecordFile->Release();
		pIReadRecordFile = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

