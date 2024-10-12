#include "DebugRestriction.hxx"
#ifdef _DEBUG
#include <iostream>

void _DebugInit()
{
	AllocConsole();
	freopen("CON", "r", stdin);     // �W�����͂̊��蓖��
	freopen("CON", "w", stdout);    // �W���o�͂̊��蓖��
}

bool _falseCheckFunc(bool b)
{
	if (!b) {
		OutputDebugString("���������� !-!-!-! ���������� �Ffalse���Ԃ���܂����B\n");
		DebugBreak();
	}
	return b;
}

HRESULT _HResultCheckFunc(HRESULT hr)
{
	if (FAILED(hr)) {
		OutputDebugString("���������� !-!-!-! ���������� �FHRESULT�����s���܂����B\n");
		DebugBreak();
	}
	return hr;
}

void _DebugStringOutput(const std::string& str)
{
	std::cout << str.c_str() << std::endl;
}

#endif // _DEBUG