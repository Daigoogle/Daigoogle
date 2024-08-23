//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	ファイル名：ColliderJudgement.cuh
//	概要		 ：当たり判定の計算をGPUにぶん投げる
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/01/20	19:20	作成	
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____COLLIDER_JUDGEMENT_CUH_____
#define _____COLLIDER_JUDGEMENT_CUH_____

#include "ColliderManager.h"
#include "Vectors.hxx"
#include <vector>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

class ColliderJudgement
{
//	-----　ホスト(CPU)　-----
public:
	__host__ ColliderJudgement();
	//__host__ ~ColliderJudgement();

	__host__ void SetCubeCollision(std::vector<ColliderBase>) {}
	__host__ void SetDotCollision(std::vector<ColliderBase>) {}

	__host__ void HitJudgement();

private:
	std::vector<fVec3> m_CubeFrame;


//	-----　ゲスト(GPU)　-----
public:

private:

};



#endif // !_____COLLIDER_JUDGEMENT_CUH_____