#include "DebugRestriction.hxx"
#ifdef _DEBUG

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

#endif // _DEBUG