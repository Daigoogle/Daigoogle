//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	�t�@�C�����FColliderManager.h
//	�T�v		 �F�e�����蔻��̊�ƂȂ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/01/21	16:39	�쐬	
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____COLLIDER_BASE_H_____
#define _____COLLIDER_BASE_H_____

#include "Transform.h"
#include <memory>

enum JudgeTag
{
	JUDGE_GROUND = 0,
	JUDGE_PLAYER,
	JUDGE_GOAL,
	JUDGE_TAGMAX
};

enum CollisionType
{
	COLLISION_DOT = 0,
	COLLISION_CUBE,
	COLLISION_MAX
};

class ColliderBase
{
public:
	ColliderBase();
	~ColliderBase();

	virtual void Draw();

	std::shared_ptr<Transform> GetTransform();
	void SetBaseTransform(std::shared_ptr<Transform>);
	JudgeTag GetTag();
	void SetTag(JudgeTag);
	CollisionType GetType();
protected:
	std::shared_ptr<Transform> m_BaseTransform;
	std::shared_ptr<Transform> m_CollTransform;
	std::shared_ptr<ColliderBase*> m_Me;
	CollisionType m_Type;
	JudgeTag m_Tag;
};

#endif // !_____COLLIDER_BASE_H_____