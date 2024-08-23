#include "ColliderManager.h"


ColliderManager::ColliderManager()
	:Singleton(UPDATE_ORDER::SECOND_UPDATE)
{
}


ColliderManager::~ColliderManager()
{
	UnInit();
}
bool ColliderManager::Init()
{
	//m_ColliderJudgement = std::make_unique<ColliderJudgement>();

	return true;
}
void ColliderManager::Update()
{
	//for(int i = 0;i < m_Collisions.size();i++)
	//{
	//	if (!m_Collisions[i].lock())
	//	{
	//		m_Collisions.erase(m_Collisions.begin() + i);
	//		i--;
	//	}
	//}


	//m_ColliderJudgement.get()->HitJudgement();
}
//void ColliderManager::Draw();
void ColliderManager::UnInit()
{
	//m_ColliderJudgement.release();
}

void ColliderManager::AddCollision(std::weak_ptr<ColliderBase*> add)
{
	//if(add.lock())
	//	m_Collisions.push_back(add);
}

std::vector<std::weak_ptr<ColliderBase*>> ColliderManager::GetCollisions()
{
	return m_Collisions;
}