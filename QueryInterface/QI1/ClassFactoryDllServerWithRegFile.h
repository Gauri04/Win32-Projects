#include<Windows.h>
class ISum : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};

class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};

class IMultiply : public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};

// CLSID of SumSubtract component
const CLSID CLSID_SumSubtract =   // {C86FE958-919D-4A5A-A81D-6098D4AF7F55}
{0xc86fe958, 0x919d, 0x4a5a, 0xa8, 0x1d, 0x60, 0x98, 0xd4, 0xaf, 0x7f, 0x55};

const IID IID_ISum =			// {C3FC1FC2-23CB-4E6C-86DC-8B13D4E36B2E}
{ 0xc3fc1fc2, 0x23cb, 0x4e6c, 0x86, 0xdc, 0x8b, 0x13, 0xd4, 0xe3, 0x6b, 0x2e };

const IID IID_ISubtract = // {57D02006-2539-4ABD-9D6E-D85C75D70FFC}
{ 0x57d02006, 0x2539, 0x4abd, 0x9d, 0x6e, 0xd8, 0x5c, 0x75, 0xd7, 0xf, 0xfc };

const IID IID_IMultiply = // {5C8DFDDC-0069-435A-A8C0-7FA9D17DBD1D}
{ 0x5c8dfddc, 0x69, 0x435a, 0xa8, 0xc0, 0x7f, 0xa9, 0xd1, 0x7d, 0xbd, 0x1d };











