#include "SkyBoxManager.h"
#include "CameraManager.h"

SkyBoxManager::SkyBoxManager()
	: Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

SkyBoxManager::~SkyBoxManager()
{
	UnInit();
}

bool SkyBoxManager::Init()
{
	// 元データの 
	Vertex vtx[] = {
		//-z面
		{{-100.0f, 100.0f,-100.0f},{0.998f,0.3333f}},//0
		{{ 100.0f, 100.0f,-100.0f},{0.75f, 0.3333f}},//1
		{{-100.0f,-100.0f,-100.0f},{0.998f,0.66f}},//2
		{{ 100.0f,-100.0f,-100.0f},{0.75f, 0.66f}},//3
		//z
		{{-100.0f, 100.0f,100.0f},{0.25f,0.3333f}},//4
		{{ 100.0f, 100.0f,100.0f},{0.50f,0.3333f}},//5
		{{-100.0f,-100.0f,100.0f},{0.25f,0.66f}},//6
		{{ 100.0f,-100.0f,100.0f},{0.50f,0.66f}},//7
		//-x
		{{ -100.0f, 100.0f,-100.0f},{0.002f,0.3333f}},//0
		{{ -100.0f, 100.0f, 100.0f},{0.25f,0.3333f}},//4
		{{ -100.0f,-100.0f,-100.0f},{0.002f,0.66f}},//2
		{{ -100.0f,-100.0f, 100.0f},{0.25f,0.66f}},//6
		//x
		{{ 100.0f, 100.0f,-100.0f},{0.75f,0.3333f}},//1
		{{ 100.0f, 100.0f, 100.0f},{0.50f,0.3333f}},//5
		{{ 100.0f,-100.0f,-100.0f},{0.75f,0.66f}},//3
		{{ 100.0f,-100.0f, 100.0f},{0.50f,0.66f}},//7
		//-y
		{{ -100.0f,-100.0f,-100.0f},{0.25f,0.66f}},//2
		{{ -100.0f,-100.0f, 100.0f},{0.50f,0.66f}},//6
		{{  100.0f,-100.0f,-100.0f},{0.25f,0.998f}},//3
		{{  100.0f,-100.0f, 100.0f},{0.50f,0.998f}},//5

		//y
		{{ -100.0f, 100.0f,-100.0f},{0.50f,0.0f} 	},//0
		{{ -100.0f, 100.0f, 100.0f},{0.25f,0.0f} 	},//4
		{{  100.0f, 100.0f,-100.0f},{0.5f,0.3333f}	},//1
		{{  100.0f, 100.0f, 100.0f},{0.25f,0.3333f} },//5
	};

	//int idx[] = {
	//	0,1,2,		1,3,2,		//-Z面
	//	6,5,4,		6,7,5,		//Z面
	//	10,9,0,		10,11,9,	//-x
	//	12,13,14,	13,15,14,	//x
	//	18,17,16,	18,19,17,	//-y
	//	0,21,22,	21,23,22,	//y
	//};
	int idx[] = {		
		0,2,1,		1,2,3,		//-Z面
		6,4,5,		6,5,7,		//Z面
		10,8,9,		10,9,11,	//-x
		12,14,13,	13,14,15,	//x
		18,16,17,	18,17,19,	//-y
		20,22,21,	21,22,23,		//y
	};

	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);
	desc.vtxSize = 20;//20;
	desc.pIdx = idx;
	desc.idxCount = 36;
	desc.idxSize = sizeof(int);//4;
	desc.topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_MeshBuffer = std::make_unique<MeshBuffer>(desc);

	return true;
}

void SkyBoxManager::Draw()
{
	CameraBase* Camm = Singleton<CameraManager>::GetInstance().GetMainCamera();
	while (!m_queue.empty())
	{
		// データの取り出し
		SkyBoxComponent* pSpriteComp = m_queue.front();
		m_queue.pop();

		// トランスフォームを取得
		Transform* pTransform = pSpriteComp->GetTransform();

		// パラメータの取り出し
		VertexShader* pVtxShader = pSpriteComp->GetVertexShader();
		PixelShader* pPixelShader = pSpriteComp->GetPixelShader();
		fVec4 color = pSpriteComp->GetColor();
		fVec2 uvOffset = pSpriteComp->GetUVOffset();
		fVec2 uvScale = pSpriteComp->GetUVScale();
		std::vector<std::shared_ptr<char[]>>& vtxShaderData = pSpriteComp->GetVertexShaderWriteData();
		std::vector<std::shared_ptr<char[]>>& pixelShaderData = pSpriteComp->GetPixelShaderWriteData();
		Texture* pTexture = pSpriteComp->GetTexture();

		float afVtxInfos[] = {
			uvOffset.x,
			uvOffset.y,
			uvScale.x,
			uvScale.y,
			color.x,
			color.y,
			color.z,
			color.w
		};

		// ワールド行列の取り出し
		DirectX::XMFLOAT4X4 mat[3];
		mat[0] = pTransform->GetWorldMatrix();

		// カメラのデータを取り出すループ
		//CCameraManager& camManager = CameraManager::GetInstance();

			// カメラの行列の取り出し
		mat[1] = Camm->GetViewMatrix();
		mat[2] = Camm->GetProjMatrix();

		// 頂点シェーダへの書き込み処理
		pVtxShader->WriteBuffer(0, mat);
		pVtxShader->WriteBuffer(1, afVtxInfos);
		int nNoInfo = 2;
		for (int nCntInfo = 0; nCntInfo < vtxShaderData.size(); nCntInfo++)
		{
			pVtxShader->WriteBuffer(nNoInfo, vtxShaderData[nCntInfo].get());
			nNoInfo++;
		}
		pVtxShader->Bind();

		// ピクセルシェーダへの書き込み処理
		for (int nCntInfo = 0; nCntInfo < pixelShaderData.size(); nCntInfo++)
		{
			pPixelShader->WriteBuffer(nCntInfo, pixelShaderData[nCntInfo].get());
		}
		pPixelShader->SetTexture(0, pTexture);
		pPixelShader->Bind();

		// メッシュバッファ
		m_MeshBuffer->Draw();
	}
}

void SkyBoxManager::UnInit()
{
	m_MeshBuffer.release();

}

void SkyBoxManager::AddQueue(SkyBoxComponent* pComp)
{
	m_queue.push(pComp);
}