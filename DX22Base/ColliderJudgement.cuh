//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	�t�@�C�����FColliderJudgement.cuh
//	�T�v		 �F�����蔻��̌v�Z��GPU�ɂԂ񓊂���
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/01/20	19:20	�쐬	
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
//	-----�@�z�X�g(CPU)�@-----
public:
	__host__ ColliderJudgement();
	//__host__ ~ColliderJudgement();

	__host__ void SetCubeCollision(std::vector<ColliderBase>) {}
	__host__ void SetDotCollision(std::vector<ColliderBase>) {}

	__host__ void HitJudgement();

private:
	std::vector<fVec3> m_CubeFrame;


//	-----�@�Q�X�g(GPU)�@-----
public:

private:

};



#endif // !_____COLLIDER_JUDGEMENT_CUH_____