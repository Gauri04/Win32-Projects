#include<windows.h>

class ISum : public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_SumSubtract = // {0F7EACD3-1721-46B5-8FFF-3D557CCCFC27}
{ 0xf7eacd3, 0x1721, 0x46b5, 0x8f, 0xff, 0x3d, 0x55, 0x7c, 0xcc, 0xfc, 0x27 };

const IID IID_ISum = // {3009230C-FE2B-4CDC-AC84-C09085636C7C}
{ 0x3009230c, 0xfe2b, 0x4cdc, 0xac, 0x84, 0xc0, 0x90, 0x85, 0x63, 0x6c, 0x7c };

const IID IID_ISubtract = // {C2443FF1-D798-4494-BBD1-D10EABB6EE34}
{ 0xc2443ff1, 0xd798, 0x4494, 0xbb, 0xd1, 0xd1, 0xe, 0xab, 0xb6, 0xee, 0x34 };

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












