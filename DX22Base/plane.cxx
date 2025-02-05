#include "Plane.hxx"
#include "RenderMng.hxx"
#include "GameObject.hxx"
#include "CameraManager.h"

Plane::Plane()
	: m_IsBillboard(false)
{
}

Plane::~Plane()
{

}

bool Plane::Init()
{
	m_pMeshBuffer = RenderMng::GetInstance().GetMeshBuffer(MESH_plane);
	m_VertexShader = RenderMng::GetInstance().GetVertexShader("Assets/Shader/Sprite3D_Defalt_VS.cso");
	m_PixelShader = RenderMng::GetInstance().GetPixelShader("Assets/Shader/Sprite3D_Defalt_PS.cso");
	Render::InitSetting();
	m_Transform = GetGameObject()->GetTransform();
	return true;
}

void Plane::Draw()
{
	CameraBase* Camm = CameraManager::GetInstance().GetMainCamera();

	float afVtxInfos[8];/* = {
		m_uvOffSet.x,
		m_uvOffSet.y,
		m_uvScale.x,
		m_uvScale.y,
		m_Color.x,
		m_Color.y,
		m_Color.z,
		m_Color.w
	};*/
	if (m_uvOffSet)
	{
		afVtxInfos[0] = m_uvOffSet->x;
		afVtxInfos[1] = m_uvOffSet->y;
	}
	else
	{
		afVtxInfos[0] = 0.0f;
		afVtxInfos[1] = 0.0f;
	}
	if (m_uvScale)
	{
		afVtxInfos[2] = m_uvScale->x;
		afVtxInfos[3] = m_uvScale->y;
	}
	else
	{
		afVtxInfos[2] = 1.0f;
		afVtxInfos[3] = 1.0f;
	}
	if (m_Color)
	{
		afVtxInfos[4] = m_Color->x;
		afVtxInfos[5] = m_Color->y;
		afVtxInfos[6] = m_Color->z;
		afVtxInfos[7] = m_Color->w;
	}
	else
	{
		afVtxInfos[4] = 1.0f;
		afVtxInfos[5] = 1.0f;
		afVtxInfos[6] = 1.0f;
		afVtxInfos[7] = 1.0f;
	}

	// ワールド行列の取り出し
	DirectX::XMFLOAT4X4 mat[3];
	mat[0] = m_Transform->GetWorldMatrix();

	// カメラのデータを取り出すループ
	//CCameraManager& camManager = CameraManager::GetInstance();

		// カメラの行列の取り出し
	mat[1] = Camm->GetViewMatrix();
	mat[2] = Camm->GetProjMatrix();

	// 頂点シェーダへの書き込み処理
	m_VertexShader->WriteBuffer(0, mat);
	m_VertexShader->WriteBuffer(1, afVtxInfos);
	int nNoInfo = 2;
	for (int nCntInfo = 0; nCntInfo < m_vtxShaderWriteDatas.size(); nCntInfo++, nNoInfo++)
	{
		m_VertexShader->WriteBuffer(nNoInfo, m_vtxShaderWriteDatas[nCntInfo].get());
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