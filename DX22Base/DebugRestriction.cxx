#include "DebugRestriction.hxx"
#ifdef _DEBUG
#include <windows.h>

void* IsNullptr(void* ptr)
{
	if (!ptr) {
		OutputDebugString("[ nullptr ]���������܂����B�Q�ƁE�ˑ��֌W���������Ă��������B");
		DebugBreak();
	}
	return ptr;
}

#endif // _DEBUG