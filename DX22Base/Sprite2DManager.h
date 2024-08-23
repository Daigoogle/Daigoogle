//	ファイル名：Sprite2DManager.h
//	概要		 ：2D平面オブジェクトの管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/18	00:52	コメント追加
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____SPRITE_2D_MANAGER_H_____
#define _____SPRITE_2D_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include "Sprite2DComponent.h"
#include "MeshBuffer.h"
#include <memory>
#include <queue>
#include "SingletonsMng.hxx"

/// @brief 2D平面オブジェクトの管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class Sprite2DManager final :public Singleton<Sprite2DManager>
{
	friend Singleton<Sprite2DManager>;
public:
	bool	Init(void);
	void	Draw(void);
	void	UnInit(void);
	void	AddQueue(Sprite2DComponent*);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	//	SetWindowSize
	//	関数概要：ウィンドウサイズを設定
	//	クラス：CSprite2DManager
	//	引　数：なし
	//	返り値：なし
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	void	SetWindowSize();

private:
	Sprite2DManager();	//コンストラクタ
	~Sprite2DManager();	//デストラクタ

	std::unique_ptr<MeshBuffer>		m_meshBuffer;
	std::queue<Sprite2DComponent*>	m_queue;
	fVec2 m_windowSize;
	static const float				NEAR_CLIP;
	static const float				FAR_CLIP;
};

#endif // !_____SPRITE_2D_MANAGER_H_____