#include<windows.h>
#include<stdio.h>
#include"AutomationServerWithRegFileUpdated.h"

class CMyMath : public IMyMath {

private:
	long m_cRef;
	ITypeInfo *m_pITypeInfo;

public:
	CMyMath(void);
	~CMyMath(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall GetTypeInfoCount(UINT *);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo **);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);

	HRESULT InitInstance(void);
};

class CMyMathClassFactory : public IClassFactory {
private:
	long m_cRef;
public:
	CMyMathClassFactory(void);
	~CMyMathClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumbberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// Below is the guid of TypeLibrary. Same guid is used in REG file
const GUID LIBID_AutomationServer =
// {0231D332-04F2-4CFD-9D11-5EB7CD434743}
{ 0x231d332, 0x4f2, 0x4cfd, 0x9d, 0x11, 0x5e, 0xb7, 0xcd, 0x43, 0x47, 0x43 };



BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {

	case DLL_PROCESS_ATTACH:
		MessageBox(NULL, TEXT("Automation server->In DllMain-process attach"), TEXT("INFO"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(NULL, TEXT("Automation server->In DllMain-process detach"), TEXT("INFO"), MB_OK);
		break;
	}
	return(TRUE);
}

CMyMath::CMyMath(void) {
	m_cRef = 1;
	m_pITypeInfo = NULL;
	InterlockedIncrement(&glNumbberOfActiveComponents);
}

CMyMath::~CMyMath(void) {
	InterlockedDecrement(&glNumbberOfActiveComponents);
}

HRESULT CMyMath::QueryInterface(REFIID riid, void ** ppv) {
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath *>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath *>(this);
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath *>(this);
	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("Server->CMyMath->QI ppv not matched"), TEXT("ERROR"), MB_OK);
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMath::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMath::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CMyMath::GetTypeInfoCount(UINT *pCountTypeInfo) {
	*pCountTypeInfo = 1;
	return(S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo) {
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
		return(DISP_E_BADINDEX);
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId) {
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
	VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr) {
	HRESULT hr;
	hr = DispInvoke(this, m_pITypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	return(hr);
}

HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int * num3) {
	*num3 = num1 + num2;
	return(S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int * num3) {
	*num3 = num1 - num2;
	return(S_OK);
}

HRESULT CMyMath::InitInstance(void) {
	void ComErrorDescriptionString(HWND, HRESULT);

	HRESULT hr;
	ITypeLib *pITypeLib = NULL;

	if (m_pITypeInfo == NULL) {
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);

		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			MessageBox(NULL, TEXT("Server->CMyMath->InitInstance typelib not loaded"), TEXT("ERROR"), MB_OK);
			return(hr);
		}

		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			MessageBox(NULL, TEXT("Server->CMyMath->InitInstance error in GetTypeInfoOfGuid"), TEXT("ERROR"), MB_OK);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return(S_OK);
}



CMyMathClassFactory::CMyMathClassFactory(void) {
	m_cRef = 1;
}

CMyMathClassFactory::~CMyMathClassFactory(void) {

}

HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void ** ppv) {
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);

	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("Server->ClassFactory->QI ppv not matched"), TEXT("ERROR"), MB_OK);
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMathClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMathClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}

	return(m_cRef);
}

HRESULT CMyMathClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {
	CMyMath *pCMyMath = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		MessageBox(NULL, TEXT("CMyMathClassFactory-CreateInstance no aggregation"), TEXT("ERROR"), MB_OK);
		return(CLASS_E_NOAGGREGATION);
	}

	pCMyMath = new CMyMath;

	if (pCMyMath == NULL) {
		MessageBox(NULL, TEXT("CMyMathClassFactory-CreateInstance CMyMath not initialized"), TEXT("ERROR"), MB_OK);
		return(E_OUTOFMEMORY);
	}
	pCMyMath->InitInstance();
	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return(hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock) {
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedIncrement(&glNumberOfServerLocks);
	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	CMyMathClassFactory *pCMyMathClassFactory;
	HRESULT hr;

	if (rclsid != CLSID_MyMath) {
		MessageBox(NULL, TEXT("Automation Server-> DllGetCasssObject Class id not obtained"), TEXT("ERROR"), MB_OK);
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL) {
		MessageBox(NULL, TEXT("Automation Server-> DllGetClassObject class factory initialization erorr"), TEXT("ERROR"), MB_OK);
		return(E_OUTOFMEMORY);
	}

	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumbberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr) {
	TCHAR *szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&szErrorMessage, 0, NULL) != 0) {
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else {
		swprintf_s(str, TEXT("[Could not find a description for error # % #x.]\n"), hr);
	}

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}
































