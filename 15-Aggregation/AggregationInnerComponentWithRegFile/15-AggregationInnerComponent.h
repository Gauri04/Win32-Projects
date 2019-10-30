#include<windows.h>

class IMultiplication : public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision : public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwonIntegers(int, int, int*) = 0;
};

const CLSID CLSID_MultiplicationDivision = // {10CD8B6F-51D3-4D3A-91C6-D070A8C42FB2}
{ 0x10cd8b6f, 0x51d3, 0x4d3a, 0x91, 0xc6, 0xd0, 0x70, 0xa8, 0xc4, 0x2f, 0xb2 };


const IID IID_IMultiplication = // {E39C6AEC-2085-4AD2-92F9-D5FB88F793F1}
{ 0xe39c6aec, 0x2085, 0x4ad2, 0x92, 0xf9, 0xd5, 0xfb, 0x88, 0xf7, 0x93, 0xf1 };


const IID IID_IDivision = // {88177F37-D215-47B5-979A-F398D237C517}
{ 0x88177f37, 0xd215, 0x47b5, 0x97, 0x9a, 0xf3, 0x98, 0xd2, 0x37, 0xc5, 0x17 };
