#pragma once
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




