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





