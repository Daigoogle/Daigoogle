//	ファイル名：Sprite3DManager.h
//	概要		 ：3Dの平面オブジェクトの管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/17	21:40	コメント追加
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____SPRITE_3D_MANAGER_H_____
#define _____SPRITE_3D_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include "MeshBuffer.h"
#include "CameraBase.h"
#include <queue>
#include <memory>
#include "Sprite3DComponent.h"
#include "SingletonsMng.hxx"

/// @brief 3D空間上の平面オブジェクトを管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class Sprite3DManager :public Singleton<Sprite3DManager>
{
	friend Singleton<Sprite3DManager>;
private:
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};
public:
	bool Init();
	void Draw();
	void UnInit();
	void AddQueue(Sprite3DComponent*);
private:
	Sprite3DManager();
	~Sprite3DManager();
	std::unique_ptr<MeshBuffer> m_MeshBuffer;
	std::queue<Sprite3DComponent*> m_queue;

};

#endif // !_____SPRITE_3D_MANAGER_H_____