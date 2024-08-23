#include "CubeCollisionToDirectComponent.h"
#include "CubeCollisionToDirectManager.h"

void CubeCollisionToDirectComponent::SetTransform(Transform* tf)
{
	m_Transform = tf;
}

Transform* CubeCollisionToDirectComponent::GetTransform()
{
	return m_Transform;
}

void CubeCollisionToDirectComponent::SetTag(CollisionTag tag)
{
	m_Tag = tag;
}

CollisionTag CubeCollisionToDirectComponent::GetTag()
{
	return m_Tag;
}

void CubeCollisionToDirectComponent::Commit()
{
	CubeCollisionToDirectManager::GetInstance().AddCollision(this);
}