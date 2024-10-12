#include "DebugRestriction.hxx"
#ifdef _DEBUG
#include <iostream>

void _DebugInit()
{
	AllocConsole();
	freopen("CON", "r", stdin);     // 標準入力の割り当て
	freopen("CON", "w", stdout);    // 標準出力の割り当て
}

bool _falseCheckFunc(bool b)
{
	if (!b) {
		OutputDebugString("■◆■◆■ !-!-!-! ■◆■◆■ ：falseが返されました。\n");
		DebugBreak();
	}
	return b;
}

HRESULT _HResultCheckFunc(HRESULT hr)
{
	if (FAILED(hr)) {
		OutputDebugString("■◆■◆■ !-!-!-! ■◆■◆■ ：HRESULTが失敗しました。\n");
		DebugBreak();
	}
	return hr;
}

void _DebugStringOutput(const std::string& str)
{
	std::cout << str.c_str() << std::endl;
}

#endif // _DEBUG