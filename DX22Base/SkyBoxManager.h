//	ファイル名：CubeManager.h
//	概要		 ：立方体の管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/09	03:07	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____SKY_BOX_MANAGER_H_____
#define _____SKY_BOX_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include <queue>
#include "CameraBase.h"
#include "MeshBuffer.h"
#include "SkyBoxComponent.h"
#include "SingletonsMng.hxx"

/// @brief 立方体の管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class SkyBoxManager final :public Singleton<SkyBoxManager>
{
	friend class Singleton<SkyBoxManager>;
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
	void AddQueue(SkyBoxComponent*);

private:
	SkyBoxManager();
	~SkyBoxManager();

	std::unique_ptr<MeshBuffer> m_MeshBuffer;
	std::queue<SkyBoxComponent*> m_queue;
};

#endif // !_____SKY_BOX_MANAGER_H_____