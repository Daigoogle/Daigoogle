//	ColliderJudgement.cu

#include "ColliderJudgement.cuh"

__host__ ColliderJudgement::ColliderJudgement()
{
	m_CubeFrame.push_back({ -0.5f, 0.5f,-0.5f });//0
	m_CubeFrame.push_back({  0.5f, 0.5f,-0.5f });//1
	m_CubeFrame.push_back({ -0.5f,-0.5f,-0.5f });//2
	m_CubeFrame.push_back({  0.5f,-0.5f,-0.5f });//3
	m_CubeFrame.push_back({ -0.5f, 0.5f, 0.5f });//4
	m_CubeFrame.push_back({  0.5f, 0.5f, 0.5f });//5
	m_CubeFrame.push_back({ -0.5f,-0.5f, 0.5f });//6
	m_CubeFrame.push_back({  0.5f,-0.5f, 0.5f });//7
}

__host__ ColliderJudgement::~ColliderJudgement()
{
}

__host__ void ColliderJudgement::HitJudgement()
{
	char* D_Ans[JudgeTag::JUDGE_TAGMAX];
	
	dim3 block, grid;//グリッド内にブロック

}