#include<Windows.h>
#include<fstream>
#include "ClassFactoryDllServerWithRegFile.h"

class CRecordFile : public IReadRecordFile, IWriteRecordFile {

private:
	long m_cRef;
	FILE *fp;

public:
	CRecordFile(void);
	~CRecordFile(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall ReadRecord(char **);
	HRESULT __stdcall WriteRecord(char[][200]);
};

class CSumSubtractClassFactory : public IClassFactory {

private:
	long m_cRef;

public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};


long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) {

	switch (dwReason) {

	case DLL_PROCESS_ATTACH:
		MessageBox(NULL, TEXT("Server->Process attach"), TEXT("DebugInfo"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(NULL, TEXT("Server->Process detach"), TEXT("DebugInfo"), MB_OK);
		break;
	}

	return(TRUE);
}

CRecordFile::CRecordFile(void) {
	m_cRef = 1;
	MessageBox(NULL, TEXT("Server->CoClass constructor "), TEXT("DebugInfo"), MB_OK);
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CRecordFile::~CRecordFile(void) {
	MessageBox(NULL, TEXT("Server->CoClass destructor "), TEXT("DebugInfo"), MB_OK);
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CRecordFile::QueryInterface(REFIID riid, void ** ppv) {

	if (riid == IID_IUnknown)
		*ppv = static_cast<IReadRecordFile *>(this);

	else if (riid == IID_IReadRecordFile)
		*ppv = static_cast<IReadRecordFile *>(this);

	else if (riid == IID_IWriteRecordFile)
		*ppv = static_cast<IWriteRecordFile *>(this);

	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("Server->CoClass QI ppv not found"), TEXT("DebugError"), MB_OK);
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);

}

ULONG CRecordFile::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CRecordFile::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}


// ********** Implementation of file Read and Write methods **************************
HRESULT CRecordFile::ReadRecord(char** outBuffer) {
	wchar_t str[255];

	// temporary buffer to check read opration is successful or not, if successful, will use outBuffer instead.
	char buffer[2000];
	MessageBox(NULL, TEXT("Server->CoClass ReadRecord"), TEXT("DebugInfo"), MB_OK);
	fopen_s(&fp, "D:\\data.txt", "r");
	if (fp == NULL) {
		MessageBox(NULL, TEXT("Error initializing file pointer (Read)"), TEXT("ERROR"), MB_OK);
		return(S_FALSE);
	}
	
	// Method 1 for reading file : Not working
	/*for (int i = 0; ferror(fp); i++) {
			fscanf_s(fp, "%s", buffer);
	} */

	// Method 2 for reading file : Not working
	while ((fscanf_s(fp, "%s", &buffer)) != EOF) {
		printf("%s", buffer);
	} 

	// To check whether data is there in buffer[]
	wsprintf(str, TEXT("Data: %s"), buffer);
	MessageBox(NULL, str, TEXT("Result"), MB_OK);

	MessageBox(NULL, TEXT("Server->CoClass ReadRecord reading successful"), TEXT("DebugInfo"), MB_OK);
	fclose(fp);
	return(S_OK);
}

HRESULT CRecordFile::WriteRecord(char inBuffer[][200]) {
	MessageBox(NULL, TEXT("Server->CoClass WriteRecord"), TEXT("DebugInfo"), MB_OK);
	fopen_s(&fp, "D:\\data.txt", "a");
	if (fp == NULL) {
		MessageBox(NULL, TEXT("Error initializing file pointer (Write)"), TEXT("ERROR"), MB_OK);
		return(S_FALSE);
	}

	// Method 1 for writing file : Not working
	/*while (length != 0) {
		fprintf(fp, "%s", inBuffer);
		length--;
	}
	 */

	// Method 2 for writing file : Working
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 200; j++) {
			if (inBuffer[i][j] != '\0') {
				fprintf(fp, "%c", inBuffer[i][j]);
			}
		}
		fprintf(fp, "\t");
	}
	fprintf(fp, "\n");

	fclose(fp);
	return(S_OK);
}

// *********************** ClassFactory methods implementation *********************************

CSumSubtractClassFactory::CSumSubtractClassFactory(void) {
	m_cRef = 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void) {

}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv) {

	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);

	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);

	else {
		*ppv = NULL;
		MessageBox(NULL, TEXT("Server->ClassFactory QI ppv not found"), TEXT("DebugError"), MB_OK);
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
	CRecordFile *pCRecordFile = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCRecordFile = new CRecordFile;

	if (pCRecordFile == NULL) {
		MessageBox(NULL, TEXT("Server->ClassFactory->CreateInstance error in intitializing CoClass "), TEXT("DebugErrror"), MB_OK);
		return(E_OUTOFMEMORY);
	}


	hr = pCRecordFile->QueryInterface(riid, ppv);
	pCRecordFile->Release();

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

	MessageBox(NULL, TEXT("Server->In DllGetClassObject "), TEXT("DebugInfo"), MB_OK);
	CSumSubtractClassFactory *pCSumSubtractClassFactory;
	HRESULT hr;

	if (rclsid != CLSID_CRecordFile) {
		MessageBox(NULL, TEXT("Server->In DllGetClassObject clsid not found"), TEXT("DebugError"), MB_OK);
		return(CLASS_E_CLASSNOTAVAILABLE);
	}

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	MessageBox(NULL, TEXT("Server->DllGetClassObject success initializing ClassFactory "), TEXT("DebugInfo"), MB_OK);

	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);

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

























