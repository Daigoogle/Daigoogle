#ifndef _____CUBE_COLLISION_TO_DIRECT_COMPONENT_H_____
#define _____CUBE_COLLISION_TO_DIRECT_COMPONENT_H_____

#include "Transform.h"

enum CollisionTag
{
	PLAYER = 0,
	GROUND,
	GOAL,
	TAG_MAX
};

class CubeCollisionToDirectComponent
{
public:
	void SetTransform(Transform* tf);
	Transform* GetTransform();
	void SetTag(CollisionTag tag);
	CollisionTag GetTag();
	void Commit();
private:
	Transform* m_Transform;
	CollisionTag m_Tag;
};

#endif // !_____CUBE_COLLISION_TO_DIRECT_H_____