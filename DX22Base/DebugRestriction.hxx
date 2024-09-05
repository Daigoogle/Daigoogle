//	ファイル名	：DebugRestriction.hxx
//	  概  要		：デバッグの際に使用する処理です。
//					それ以外では使用できませんので[ #ifdef _DEBUG ]で囲んでください。
//	作	成	者	：daigo
//	 作成日時	：2024/09/06 3:17:38
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____DebugRestriction_HXX_____
#define _____DebugRestriction_HXX_____

// =-=-= デバッグ限定処理 =-=-=
#ifdef _DEBUG

// =-=-= インクルード部 =-=-=

void* IsNullptr(void*);


#endif // _DEBUG
#endif // !_____DebugRestriction_HXX_____