#include "DebugRestriction.hxx"	

#ifdef _DEBUG
#include <iostream>				

bool _falseCheckFunc(bool b)
{
	if (!b) {
		_DebugStringOutput("���������� !-!-!-! ���������� �Ffalse���Ԃ���܂����B\n");
		DebugBreak();
	}
	return b;
}

HRESULT _HResultCheckFunc(HRESULT hr)
{
	if (FAILED(hr)) {
		_DebugStringOutput("���������� !-!-!-! ���������� �FHRESULT�����s���܂����B\n");
		DebugBreak();
	}
	return hr;
}

class CNS_None { public:	~CNS_None() { 
	//rewind(stdin); (void)getchar(); 
} };

void _DebugStringOutput(const std::string& str)
{
	static bool bInit = true;
	static CNS_None none;
	if (bInit) {
		AllocConsole();
		(void)freopen("CON", "r", stdin);     // �W�����͂̊��蓖��
		(void)freopen("CON", "w", stdout);    // �W���o�͂̊��蓖��
		bInit = false;
	}
	std::cout << str.c_str();
}

#endif // _DEBUG