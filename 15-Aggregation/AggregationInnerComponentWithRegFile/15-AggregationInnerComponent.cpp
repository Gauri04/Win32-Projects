#include<windows.h>
#include"15-AggregationInnerComponent.h"

interface INoAggregationIUnknown {
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

class CMultiplicationDivision : public INoAggregationIUnknown, IMultiplication, IDivision {
private:
	long m_cRef;
	IUnknown *m_pIUnknownOuter;
public:
	CMultiplicationDivision(IUnknown *);
	~CMultiplicationDivision(void);

	// IUnknown's interface methods
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	
	// INoAggregationsIUnknown's interfaces methods
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwonIntegers(int, int, int*);

};

class CMultiplicationDivisionClassFactory :public IClassFactory {
public:
	long m_cRef;

	CMultiplicationDivisionClassFactory(void);
	~CMultiplicationDivisionClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory's interface methods
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->constructor"), TEXT("INFO"), MB_OK);
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	
	if (pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown *>(static_cast<INoAggregationIUnknown *>(this));
}

CMultiplicationDivision::~CMultiplicationDivision(void) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->destructor"), TEXT("INFO"), MB_OK);
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->QI"), TEXT("INFO"), MB_OK);
	return(m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CMultiplicationDivision::AddRef(void) {
	//	MessageBox(NULL, TEXT("inner->Classfactory->AddRef"), TEXT("INFO"), MB_OK);
	return(m_pIUnknownOuter->AddRef());
}

ULONG CMultiplicationDivision::Release(void) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->Release"), TEXT("INFO"), MB_OK);
	return(m_pIUnknownOuter->Release());
}

HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("Inner->QINoAggregation"), TEXT("INFO"), MB_OK);
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("Inner->QINoAggregation interface not found"), TEXT("ERROR"), MB_OK);
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivision::AddRef_NoAggregation(void) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->AddRefNoAggr"), TEXT("INFO"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation(void) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->ReleaseNoAggr"), TEXT("INFO"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int * num3) {
	*num3 = num1 * num2;
	return(S_OK);
}

HRESULT CMultiplicationDivision::DivisionOfTwonIntegers(int num1, int num2, int *num3) {
	*num3 = num1 / num2;
	return(S_OK);
}

CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void) {
	m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void) {

}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->QI"), TEXT("INFO"), MB_OK);
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);

	else {
		MessageBox(NULL, TEXT("inner->ClassFacotry->QI interface not found"), TEXT("ERROR"),MB_OK);
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef(void) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->AddRef"), TEXT("INFO"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void) {
	//	MessageBox(NULL, TEXT("inner->CMultDiv->Release"), TEXT("INFO"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("inner->ClassFactory->CreateInstance"), TEXT("INFO"), MB_OK);
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;
	
	if ((pUnkOuter != NULL) && (riid != IID_IUnknown)) {
		//		MessageBox(NULL, TEXT("inner->ClassFacotory->createInstance no aggregation"), TEXT("ERROR"), MB_OK);
		return(CLASS_E_NOAGGREGATION);
	}

	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);
	
	if (pCMultiplicationDivision == NULL) {
		MessageBox(NULL, TEXT("inner->ClassFacotory->createInstance CMultDiv class not found"), TEXT("ERROR"), MB_OK);
		return(E_OUTOFMEMORY);
	}

	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
	pCMultiplicationDivision->Release_NoAggregation();
	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock) {
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	//	MessageBox(NULL, TEXT("In inner->DllGetClassObject"), TEXT("INFO"), MB_OK);
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision) {
		MessageBox(NULL, TEXT("inner->dllgetclassobject CMultDiv class not found"), TEXT("ERROR"), MB_OK);
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;

	if (pCMultiplicationDivisionClassFactory == NULL) {
		MessageBox(NULL, TEXT("inner->DllGetclassobject CMultiplicationDivision not initialized"), TEXT("ERROR"), MB_OK);
		return(E_OUTOFMEMORY);
	}

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	if ((&glNumberOfActiveComponents == 0) && (&glNumberOfServerLocks == 0)) {
		MessageBox(NULL, TEXT("inner->dllcanunloadnow global numbers not zero"), TEXT("ERROR"), MB_OK);
		return(S_OK);
	} 
	
	else {
		return(S_FALSE);
	}
}























