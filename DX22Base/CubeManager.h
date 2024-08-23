//	ファイル名：CubeManager.h
//	概要		 ：立方体の管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/09	03:07	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____CUBE_MANAGER_H_____
#define _____CUBE_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include <queue>
#include "CameraBase.h"
#include "MeshBuffer.h"
#include "CubeComponent.h"
#include "SingletonsMng.hxx"

/// @brief 立方体の管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class CubeManager :public Singleton<CubeManager>
{
	friend Singleton<CubeManager>;
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
	void AddQueue(CubeComponent*);

private:
	CubeManager();
	~CubeManager();

	std::unique_ptr<MeshBuffer> m_MeshBuffer;
	std::queue<CubeComponent*> m_queue;
};

#endif // !_____CUBE_MANAGER_H_____