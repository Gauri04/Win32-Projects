#include<windows.h>
#include"ContainmentOuterComponentWithRegFile.h"
#include"ContainmentInnerComponentWithRegFile.h"

class CSumSubtract :public ISum, ISubtract, IMultiplication, IDivision {
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;

public :
	CSumSubtract(void);
	~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall InitializeInnerComponent(void);

};

class CSumSubtractClassFactory :public IClassFactory {
private:
	long m_cRef;

public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
	
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return(TRUE);
}


CSumSubtract::CSumSubtract(void) {
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);

	if (m_pIMultiplication) {
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}

	if (m_pIDivision) {
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
	
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv) {
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	
	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("ContainmentOuterComponent -> QI Failed to obtain ISum"), TEXT("Error"), MB_OK);
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);

}

ULONG CSumSubtract::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return(0);
	}

	return(m_cRef);
}


HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pIMultiplication) {
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pIMultiplication);
	
	return(S_OK);
}

HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int *pIdivision) {
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pIdivision);
	return(S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *num3) {
	*num3 = num1 - num2;
	return(S_OK);
}

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *num3) {
	*num3 = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void) {

	HRESULT hr;

	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication,
		(void **)&m_pIMultiplication);

	if (FAILED(hr)) {
		MessageBox(NULL,
			TEXT("ContainmentOuterComponent->InitializeInnerComponent Imultipplication interface cannot be obtained"),
			TEXT("Error"), MB_OK);
		return(E_FAIL);
	}

	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void **)&m_pIDivision);

	if (FAILED(hr)) {
		MessageBox(NULL,
			TEXT("ContainmentOuterComponent->InitializeInnerComponent IDivision interface cannot be obtained"),
			TEXT("Error"), MB_OK);
		return(E_FAIL);
	}

	return(S_OK);
}


// Implementation of ClassFacotry : CSumSubtractclassFactory methods ahead
CSumSubtractClassFactory::CSumSubtractClassFactory(void) {
	m_cRef= 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void) {

}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void ** ppv) {
	if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else if(riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);

	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("ContainmentOuterCompponent->CSumSubtractClassFactory->QI riid not obtained"), 
			TEXT("ERROR"), MB_OK);
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);

}

ULONG CSumSubtractClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {
	CSumSubtract *pCSumSubtract;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL) {
		MessageBox(NULL,
			TEXT("CaontainmentOuterComponent->CSumSubtractClassFactory->CreateInstance pCSumSubtract is NULL"),
			TEXT("Error"), MB_OK);
		return(CLASS_E_NOAGGREGATION);
	}

	hr = pCSumSubtract->InitializeInnerComponent();

	if (FAILED(hr)) {
		MessageBox(NULL,
			TEXT("CaontainmentOuterComponent->CSumSubtractClassFactory->CreateInstance falied to initialize inner component"),
			TEXT("Error"), MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);

}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock) {
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {

	MessageBox(NULL, TEXT("In DllGetClassObject of outer component"), TEXT("Info"), MB_OK);
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract) {
		MessageBox(NULL,
			TEXT("CaontainmentOuterComponent->DllGetClassObject CLSID is no CLSID_SumSubtract"),
			TEXT("Error"), MB_OK);
		return(CLASS_E_CLASSNOTAVAILABLE);
	}

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL) {
		MessageBox(NULL,
			TEXT("CaontainmentOuterComponent->DllGetClassObject NULL SumSubtract"),
			TEXT("Error"), MB_OK);
		return(E_OUTOFMEMORY);
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}



























