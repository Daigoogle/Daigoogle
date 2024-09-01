#include "plane.hxx"
#include "RenderMng.hxx"
#include "GameObject.hxx"
#include "CameraManager.h"

plane::plane()
	: m_IsBillboard(false)
{
}

plane::~plane()
{

}

bool plane::Init()
{
	if()

	m_pMeshBuffer = RenderMng::GetInstance().GetMeshBuffer("Plane");
	return true;
}

void plane::Draw()
{
	CameraBase* Camm = CameraManager::GetInstance().GetMainCamera();
	// トランスフォームを取得
	Transform& tf = this->GetGameObject().GetTransform();

	float afVtxInfos[] = {
		m_uvOffSet.x,
		m_uvOffSet.y,
		m_uvScale.x,
		m_uvScale.y,
		m_Color.x,
		m_Color.y,
		m_Color.z,
		m_Color.w
	};

	// ワールド行列の取り出し
	DirectX::XMFLOAT4X4 mat[3];
	mat[0] = tf.GetWorldMatrix();

	// カメラのデータを取り出すループ
	//CCameraManager& camManager = CameraManager::GetInstance();

		// カメラの行列の取り出し
	mat[1] = Camm->GetViewMatrix();
	mat[2] = Camm->GetProjMatrix();

	// 頂点シェーダへの書き込み処理
	m_VertexShader->WriteBuffer(0, mat);
	m_VertexShader->WriteBuffer(1, afVtxInfos);
	int nNoInfo = 2;
	for (int nCntInfo = 0; nCntInfo < m_vtxShaderWriteDatas.size(); nCntInfo++)
	{
		m_VertexShader->WriteBuffer(nNoInfo, m_vtxShaderWriteDatas[nCntInfo].get());
		nNoInfo++;
	}
	m_VertexShader->Bind();

	// ピクセルシェーダへの書き込み処理
	for (int nCntInfo = 0; nCntInfo < m_pixelShaderWriteDatas.size(); nCntInfo++)
	{
		m_PixelShader->WriteBuffer(nCntInfo, m_pixelShaderWriteDatas[nCntInfo].get());
	}
	m_PixelShader->SetTexture(0, m_pTexture);
	m_PixelShader->Bind();

	// メッシュバッファ
	m_pMeshBuffer->Draw();
}