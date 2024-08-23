//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	ファイル名：CubeColliderComponent.cuh
//	概要		 ：キューブ型の当たり判定を追加する
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/01/22	00:03	作成	
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____CUBE_COLLIDER_COMPONENT_H_____
#define _____CUBE_COLLIDER_COMPONENT_H_____

#include "ColliderBase.h"

class CubeColliderComponent :
    public ColliderBase
{
public:
    CubeColliderComponent();
    ~CubeColliderComponent();
private:
    
};

#endif // !_____CUBE_COLLIDER_COMPONENT_H_____