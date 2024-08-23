//	ファイル名：ColliderManager.h
//	概要		 ：当たり判定のオブジェクトをまとめる
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/01/20	19:20	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____COLLIDER_MANAGER_H_____
#define _____COLLIDER_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include "Model.h"
#include "Vectors.hxx"
#include <vector>
#include "ColliderBase.h"
#include "ColliderJudgement.cuh"
#include "SingletonsMng.hxx"

/// @brief 当たり判定を取得する
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class ColliderManager final :public Singleton<ColliderManager>
{
	friend class Singleton<ColliderManager>;
public:
	bool Init();
	void Update();
	void UnInit();
	
	void AddCollision(std::weak_ptr<ColliderBase*> add);

	std::vector<std::weak_ptr<ColliderBase*>> GetCollisions();

private:
	ColliderManager();
	~ColliderManager();

	std::unique_ptr<ColliderJudgement> m_ColliderJudgement;
	std::vector<std::weak_ptr<ColliderBase*>> m_Collisions;

};

#endif // !_____COLLIDER_MANAGER_H_____