#include<windows.h>

class IMultiplication : public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision : public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_MultiplicationDivision =// {BD012AAA-D755-4C2B-A231-2903A946BAF0}
{ 0xbd012aaa, 0xd755, 0x4c2b, 0xa2, 0x31, 0x29, 0x3, 0xa9, 0x46, 0xba, 0xf0 };

const IID IID_IMultiplication = // {13ED8D6A-9B64-4C7E-8A73-BE0798BF70BF}
{ 0x13ed8d6a, 0x9b64, 0x4c7e, 0x8a, 0x73, 0xbe, 0x7, 0x98, 0xbf, 0x70, 0xbf };

const IID IID_IDivision = // {F0E1C34E-C638-496E-A140-FC224BD936C6}
{0xf0e1c34e, 0xc638, 0x496e, 0xa1, 0x40, 0xfc, 0x22, 0x4b, 0xd9, 0x36, 0xc6};








