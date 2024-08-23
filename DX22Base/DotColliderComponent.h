//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	ファイル名：DotColliderComponent.cuh
//	概要		 ：点の当たり判定を追加する
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/01/22	01:17	作成	
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____DOT_COLLIDER_COMPONENT_H_____
#define _____DOT_COLLIDER_COMPONENT_H_____

#include "ColliderBase.h"

class DotColliderComponent :
	public ColliderBase
{
public:
	DotColliderComponent();
	~DotColliderComponent();
private:

};

#endif // !_____DOT_COLLIDER_COMPONENT_H_____