#include<windows.h>
#include"15-AggregationInnerComponent.h"
#include"15-AggregationOuterComponent.h"

class CSumSubtract :public ISum, ISubtract {
private:
	long m_cRef;
	IUnknown *m_pIUnknownInner;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;

public:
	CSumSubtract(void);
	~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **ppv);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractClassFactory :public IClassFactory {
private:
	long m_cRef;

public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **ppv);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	//	MessageBox(NULL, TEXT("DLL Main"), TEXT("INFO"), MB_OK);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		//		MessageBox(NULL, TEXT("DLL Main Process attach"), TEXT("INFO"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		//		MessageBox(NULL, TEXT("DLL Main Process Detach"), TEXT("INFO"), MB_OK);
		break;
	}
	return(TRUE);
}

CSumSubtract::CSumSubtract(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtract->constructor"), TEXT("INFO"), MB_OK);
	m_pIUnknownInner = NULL;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtract->destructor"), TEXT("INFO"), MB_OK);
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIUnknownInner) {
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv) {
	//	MessageBox(NULL,TEXT("outer->CSumSubtract->QI"), TEXT("INFO"), MB_OK);
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if(riid == IID_IMultiplication)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else if (riid == IID_IDivision)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));

	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtract::AddRef(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtract->AddRef"), TEXT("INFO"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtract->Release"), TEXT("INFO"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int * num3) {
	*num3 = num1 - num2;
	return(S_OK);
}

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int * num3) {
	*num3 = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtract->initializeinnercomponent"), TEXT("INFO"), MB_OK);
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision,
		reinterpret_cast<IUnknown *>(this),
		CLSCTX_INPROC_SERVER,
		IID_IUnknown,
		(void **)&m_pIUnknownInner);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IUnknown cannot be obtained from outer->initializeinner"), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}

	return(S_OK);
}


CSumSubtractClassFactory::CSumSubtractClassFactory(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtractClassFactory->Constructor"), TEXT("INFO"), MB_OK);
	m_cRef = 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtractClassFactory->destructor"), TEXT("INFO"), MB_OK);

}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtractClassFactory->QI"), TEXT("INFO"), MB_OK);
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);

}

ULONG CSumSubtractClassFactory::AddRef(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtractClassFactory->AddRef"), TEXT("INFO"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}


ULONG CSumSubtractClassFactory::Release(void) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtractClassFactory->Release"), TEXT("INFO"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}

	return(m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("outer->CSumSubtractClassFactory->CreateInstance"), TEXT("INFO"), MB_OK);
	CSumSubtract *pCSumSubtract;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL) {
		MessageBox(NULL, TEXT("outer classfactory- createinstance pcsumsubtract not found"), TEXT("ERROr"), MB_OK);
		return(E_OUTOFMEMORY);
	}
	hr = pCSumSubtract->InitializeInnerComponent();

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("outer classfactory- createinstance initialize inner component"), TEXT("ERROr"), MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock) {
	//	MessageBox(NULL, TEXT("outer->LockServer"), TEXT("INFO"), MB_OK);
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("outer->DllGetClassObject"), TEXT("INFO"), MB_OK);
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL) {
		MessageBox(NULL, TEXT("outer-> dllgetclassobject pcsumsubtractclassfacotry is null"), TEXT("ERROR"), MB_OK);
		return(E_OUTOFMEMORY);
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	//	MessageBox(NULL, TEXT("outer->DllCanUnloadNow"), TEXT("INFO"), MB_OK);
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}












