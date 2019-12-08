#include<windows.h>

class IMyMath : public IDispatch {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_MyMath =// {626674BC-57B8-42C4-85D0-56374DDB8553}
{ 0x626674bc, 0x57b8, 0x42c4, 0x85, 0xd0, 0x56, 0x37, 0x4d, 0xdb, 0x85, 0x53 };



const IID IID_IMyMath =// {27C39A8C-5AE2-4631-8AD4-A570FEC8C2A4}
{ 0x27c39a8c, 0x5ae2, 0x4631, 0x8a, 0xd4, 0xa5, 0x70, 0xfe, 0xc8, 0xc2, 0xa4 };







