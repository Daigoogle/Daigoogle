#include "ColliderBase.h"
#include "ColliderManager.h"

ColliderBase::ColliderBase()
{
	m_CollTransform.reset(new Transform);
	m_Me.reset();
	ColliderManager::GetInstance().AddCollision(m_Me);
}
ColliderBase::~ColliderBase()
{
	m_CollTransform.reset();
	m_Me.reset();
}
void ColliderBase::Draw()
{//“–‚½‚è”»’è‚Ìüo‚µ‚½‚¢‚æ‚Ë...

}
std::shared_ptr<Transform> ColliderBase::GetTransform()
{
	return m_CollTransform;
}
void ColliderBase::SetBaseTransform(std::shared_ptr<Transform> Set) 
{
	m_BaseTransform = Set;
}
JudgeTag ColliderBase::GetTag()
{
	return m_Tag;
}
void ColliderBase::SetTag(JudgeTag Set)
{
	m_Tag = Set;
}
CollisionType ColliderBase::GetType()
{
	return m_Type;
}