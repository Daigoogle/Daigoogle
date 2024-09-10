//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//	ファイル名：easing.h
//	概　　　要：イージング
//	製　作　者：ItoDaigo
//
//	＝＝＝更新履歴＝＝＝
//	2023/12/08	ItoDaigo	作成
// 
//  ＝＝＝  概要  ＝＝＝
//	0.0f ~ 1.0fで値を渡すと、それに対応したEasingの値を返します。
// 
//	以下遷移グラフ参考↓↓↓↓
//	https://gizma.com/easing/
// 
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// ----------インクルードガード部----------
#ifndef _____EASING_H_____
#define _____EASING_H_____

namespace Easing
{
	float InSine(float num);
	float OutSine(float num);
	float InOutSine(float num);
	float InQuad(float num);
	float OutQuad(float num);
	float InOutQuad(float num);
	float InCubic(float num);
	float OutCubic(float num);
	float InOutCubic(float num);
	float InQuart(float num);
	float OutQuart(float num);
	float InOutQuart(float num);
	float InQuint(float num);
	float OutQuint(float num);
	float InOutQuint(float num);
	float InExpo(float num);
	float OutExpo(float num);
	float InOutExpo(float num);
	float InCirc(float num);
	float OutCirc(float num);
	float InOutCirc(float num);
	float InBack(float num);
	float OutBack(float num);
	float InOutBack(float num);
	float InElastic(float num);
	float OutElastic(float num);
	float InOutElastic(float num);
	float OutBounce(float num);
	float InBounce(float num);
	float InOutBounce(float num);
}; 

#endif // !_____EASING_H_____