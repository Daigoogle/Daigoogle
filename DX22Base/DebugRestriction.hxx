//	ファイル名	：DebugRestriction.hxx
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

// ポインタのＮＵＬＬチェック
#define NullptrCheck(ptr) _NullptrCheckFunc(ptr)
// ポインタのＮＵＬＬチェック　※セミコロン付き
#define NullptrCheck_(ptr) _NullptrCheckFunc(ptr);
// Falseなら停止します
#define FalseCheck(b) _falseCheckFunc(b)
// HResultが失敗していたら停止
#define HResultCheck(hr) _HResultCheckFunc(hr)
// ここにたどり着いたら停止　※セミコロン付き
#define DebugBreakPoint_ DebugBreak();
// デバッグ用文字列の出力　※セミコロン付き
#define DebugString_(str) _DebugStringOutput(str);

void _DebugStringOutput(const std::string& str);
template<typename Type>
Type* _NullptrCheckFunc(Type* ptr)
{
	std::string stri;
	stri += "■◆■◆■ !-!-!-! ■◆■◆■ ：";
	stri += typeid(Type).name();
	stri += " の [ nullptr ]が発生しました。参照・依存関係を見直してください。\n";
	if (!ptr) {
		_DebugStringOutput(stri.c_str());
		DebugBreak();
	}
	return ptr;
}
bool _falseCheckFunc(bool b);
HRESULT _HResultCheckFunc(HRESULT hr);

#else // Release

#define NullptrCheck(ptr) ptr
#define NullptrCheck_(ptr) 
#define FalseCheck(b) b
#define HResultCheck(hr) hr
#define DebugBreakPoint_ 
#define DebugString_(str)

#endif // _DEBUG

#endif // !_____DebugRestriction_HXX_____