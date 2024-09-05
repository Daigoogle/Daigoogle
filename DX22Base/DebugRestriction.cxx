#include "DebugRestriction.hxx"
#ifdef _DEBUG
#include <windows.h>

void* IsNullptr(void* ptr)
{
	if (!ptr) {
		OutputDebugString("[ nullptr ]が発生しました。参照・依存関係を見直してください。");
		DebugBreak();
	}
	return ptr;
}

#endif // _DEBUG