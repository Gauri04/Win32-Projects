#include<windows.h>

class ISum : public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_SumSubtract = // {DEFAECE7-060B-4124-9150-297EB5AF511C}
{ 0xdefaece7, 0x60b, 0x4124, 0x91, 0x50, 0x29, 0x7e, 0xb5, 0xaf, 0x51, 0x1c };


const IID IID_ISum = // {94AF9B9E-CAD2-4A42-98B9-E3D4A9A6CBA3}
{ 0x94af9b9e, 0xcad2, 0x4a42, 0x98, 0xb9, 0xe3, 0xd4, 0xa9, 0xa6, 0xcb, 0xa3 };



const IID IID_ISubtract = // {5C91FB2B-2D5A-4698-8D69-B638E33EA3D4}
{ 0x5c91fb2b, 0x2d5a, 0x4698, 0x8d, 0x69, 0xb6, 0x38, 0xe3, 0x3e, 0xa3, 0xd4 };

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






