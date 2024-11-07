#include "DebugRestriction.hxx"	

#ifdef _DEBUG
#include <iostream>				

bool _falseCheckFunc(bool b)
{
	if (!b) {
		_DebugStringOutput("■◆■◆■ !-!-!-! ■◆■◆■ ：falseが返されました。\n");
		DebugBreak();
	}
	return b;
}

HRESULT _HResultCheckFunc(HRESULT hr)
{
	if (FAILED(hr)) {
		_DebugStringOutput("■◆■◆■ !-!-!-! ■◆■◆■ ：HRESULTが失敗しました。\n");
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
		(void)freopen("CON", "r", stdin);     // 標準入力の割り当て
		(void)freopen("CON", "w", stdout);    // 標準出力の割り当て
		bInit = false;
	}
	std::cout << str.c_str();
}

#endif // _DEBUG