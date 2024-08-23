//	ファイル名：ModelManager.h
//	概要		 ：モデルの管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/20	00:07	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____MODEL_MANAGER_H_____
#define _____MODEL_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include <queue>
#include "ModelComponent.h"
#include "SingletonsMng.hxx"

/// @brief モデルの管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class ModelManager :public Singleton<ModelManager>
{
	friend Singleton<ModelManager>;
public:
	bool Init();
	void Update();
	void Draw();
	void UnInit();

	void AddQueue(ModelComponent* comp);

private:
	ModelManager();
	~ModelManager();
	struct tPositionCBuffer
	{
		DirectX::XMFLOAT4X4 world;		// ワールド行列
		DirectX::XMFLOAT4X4 view;		// ビュー行列
		DirectX::XMFLOAT4X4 projection;	// 射影行列
	};									//// 座標の定数バッファ

	struct tLightCBuffer
	{
		DirectX::XMFLOAT4	sourcePos;	// 光源の座標
		float				alpha;		// α値
	};									//// ライトの定数バッファ	

	std::vector<ModelComponent*>	m_modelQueue;// モデルを格納する配列
	//std::unique_ptr<VertexShader>					m_vertexShader;
	//std::unique_ptr<PixelShader>					m_pixelShader;
	tPositionCBuffer						m_posCBuf;// 座標の定数バッファ
	tLightCBuffer							m_ligCBuf;// ライティングバッファ

	std::queue<ModelComponent*> m_queue;
};

#endif // !_____MODEL_MANAGER_H_____