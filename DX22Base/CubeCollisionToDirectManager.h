
//�@�p�~�\��

#ifndef _____CUBE_COLLISION_TO_DIRECT_MANAGER_H_____
#define _____CUBE_COLLISION_TO_DIRECT_MANAGER_H_____

#include <vector>
#include "CubeCollisionToDirectComponent.h"
#include "SingletonsMng.hxx"

/// @brief ��]���Ă��Ȃ������̂̓����蔻��
/// @brief ������������ �V���O���g���ł� ������������
class CubeCollisionToDirectManager :public Singleton<CubeCollisionToDirectManager>
{
	friend class Singleton<CubeCollisionToDirectManager>;
public:
	bool Init();
	void Update();
	void UnInit();

	void AddCollision(CubeCollisionToDirectComponent* obj);

	bool PlayerTachGround();
	bool PlayerTachGoal();

	void Crear();

private:
	CubeCollisionToDirectManager();
	~CubeCollisionToDirectManager();

	std::vector<CubeCollisionToDirectComponent*> m_Collisions[CollisionTag::TAG_MAX];
	bool PlayerGlound;
};

#endif // !_____CUBE_COLLISION_TO_DIRECT_MANAGER_H_____