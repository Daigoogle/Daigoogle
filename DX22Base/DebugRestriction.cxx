#include "DebugRestriction.hxx"
#ifdef _DEBUG

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

#endif // _DEBUG