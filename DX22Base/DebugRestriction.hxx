﻿//	ファイル名	：DebugRestriction.hxx
//	  概  要		：デバッグの際に使用する処理です。
//					それ以外では使用できませんので[ #ifdef _DEBUG ]で囲んでください。
//	作	成	者	：daigo
//	 作成日時	：2024/09/06 3:17:38
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____DebugRestriction_HXX_____
#define _____DebugRestriction_HXX_____

// =-=-= インクルード部 =-=-=
#ifdef _DEBUG
#include <windows.h>
#include <string>
#endif // _DEBUG

// =-=-= マクロ定義部 =-=-=
#ifdef _DEBUG
#define DEBUG_INIT _DebugInit();
#define NullptrCheck(ptr) _NullptrCheckFunc(ptr)
#define NullptrCheck_void_(ptr) _NullptrCheckFunc(ptr);
#define FalseCheck(b) _falseCheckFunc(b)
#define HResultCheck(hr) _HResultCheckFunc(hr)
#define DebugBreakPoint_ DebugBreak();
#define DebugString_(str) _DebugStringOutput(str);
#else // Release
#define NullptrCheck(ptr) ptr
#define NullptrCheck_void_(ptr) 
#define FalseCheck(b) b
#define HResultCheck(hr) hr
#define DebugBreakPoint_ 
#define DebugString_(str)
#endif // _DEBUG

// =-=-= デバッグ限定処理 =-=-=
#ifdef _DEBUG

template<typename Type>
Type* _NullptrCheckFunc(Type* ptr)
{
	std::string stri;
	stri += "■◆■◆■ !-!-!-! ■◆■◆■ ：";
	stri += typeid(Type).name();
	stri += " の [ nullptr ]が発生しました。参照・依存関係を見直してください。\n";
	if (!ptr) {
		OutputDebugString(stri.c_str());
		DebugBreak();
	}
	return ptr;
}

void _DebugInit();
bool _falseCheckFunc(bool b);
HRESULT _HResultCheckFunc(HRESULT hr);
void _DebugStringOutput(const std::string& str);

#endif // _DEBUG
#endif // !_____DebugRestriction_HXX_____