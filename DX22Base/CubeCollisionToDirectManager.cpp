#include "CubeCollisionToDirectManager.h"

CubeCollisionToDirectManager::CubeCollisionToDirectManager()
	:Singleton(UPDATE_ORDER::SECOND_UPDATE)
{

}

CubeCollisionToDirectManager::~CubeCollisionToDirectManager()
{
	UnInit();
}

void CubeCollisionToDirectManager::Crear()
{
	for (int i = 0; i < CollisionTag::TAG_MAX; i++)
		m_Collisions[i].clear();
}
bool CubeCollisionToDirectManager::Init()
{
	return true;
}
void CubeCollisionToDirectManager::Update()
{
	for (int i = 0; i < m_Collisions[CollisionTag::PLAYER].size(); i++)
	{
		Transform* PlayerObj = m_Collisions[CollisionTag::PLAYER][i]->GetTransform();
		for (int j = 0; j < m_Collisions[CollisionTag::GROUND].size(); j++)
		{
			Transform* GroundObj = m_Collisions[CollisionTag::GROUND][j]->GetTransform();
			if (PlayerObj->GetLocalPosition() + PlayerObj->GetLocalScale() * 0.5f > GroundObj->GetLocalPosition() - GroundObj->GetLocalScale() * 0.5f &&
				PlayerObj->GetLocalPosition() - PlayerObj->GetLocalScale() * 0.5f < GroundObj->GetLocalPosition() + GroundObj->GetLocalScale() * 0.5f)
			{

				PlayerGlound = true;
				return;
			}
		}
	}
	PlayerGlound = false;
	return;
}
void CubeCollisionToDirectManager::UnInit()
{
	m_Collisions[0].clear();
	m_Collisions[1].clear();
	m_Collisions[2].clear();
}
void CubeCollisionToDirectManager::AddCollision(CubeCollisionToDirectComponent* obj)
{
	m_Collisions[obj->GetTag()].push_back(obj);
}
bool CubeCollisionToDirectManager::PlayerTachGround()
{
	return PlayerGlound;
}
bool CubeCollisionToDirectManager::PlayerTachGoal()
{
	for (int i = 0; i < m_Collisions[CollisionTag::PLAYER].size(); i++)
	{
		Transform* PlayerObj = m_Collisions[CollisionTag::PLAYER][i]->GetTransform();
		for (int j = 0; j < m_Collisions[CollisionTag::GOAL].size(); j++)
		{
			Transform* GoalObj = m_Collisions[CollisionTag::GOAL][j]->GetTransform();
			if (PlayerObj->GetLocalPosition() + PlayerObj->GetLocalScale() > GoalObj->GetLocalPosition() - GoalObj->GetLocalScale() &&
				PlayerObj->GetLocalPosition() - PlayerObj->GetLocalScale() < GoalObj->GetLocalPosition() + GoalObj->GetLocalScale())
			{
				return true;
			}
		}
	}
	return false;
}