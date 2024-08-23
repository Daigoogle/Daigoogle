//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	ファイル名：ColliderManager.h
//	概要		 ：各当たり判定の基となる
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/01/21	16:39	作成	
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