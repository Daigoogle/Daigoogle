#include "Model.hxx"
#include "RenderMng.hxx"
#include "DirectX11SetUp.h"
#include "CameraManager.h"
#include "GameObject.hxx"

Model::Model()
{

}

Model::~Model()
{

}

bool Model::Init()
{
	//AddComponent<Shader>()->Load("shader/unlitTextureVS.cso", "shader/unlitTexturePS.cso");
	
	m_VertexShader = RenderMng::GetInstance().GetVertexShader("Assets/Shader/unlitTextureVS.cso");
	m_PixelShader = RenderMng::GetInstance().GetPixelShader("Assets/Shader/unlitTexturePS.cso");
	
	return true;
}

void Model::Draw()
{
	fVec4x4 wvp[3];
	wvp[0] = GetGameObject().GetTransform()->GetWorldMatrix();
	CameraBase* cam = CameraManager::GetInstance().GetMainCamera();
	wvp[1] = cam->GetViewMatrix();
	wvp[2] = cam->GetProjMatrix();

	m_VertexShader->WriteBuffer(0, wvp);

	m_PixelShader->SetTexture(0,m_Model->SubsetArray->Material.Texture);


	DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	// �C���f�b�N�X�o�b�t�@�ݒ�
	Dx11.GetContext()->IASetIndexBuffer(m_Model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	Dx11.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (unsigned int i = 0; i < m_Model->SubsetNum; i++)
	{
		// �}�e���A���ݒ�
		//Renderer::SetMaterial(m_Model->SubsetArray[i].Material.Material);

		// �e�N�X�`���ݒ�
		if (m_Model->SubsetArray[i].Material.Texture)
			Dx11.GetContext()->PSSetShaderResources(0, 1, &m_Model->SubsetArray[i].Material.Texture);

		// �|���S���`��
		Dx11.GetContext()->DrawIndexed(m_Model->SubsetArray[i].IndexNum, m_Model->SubsetArray[i].StartIndex, 0);
	}
	
}


void Model::SetModel(const std::string& path)
{
	m_Model = RenderMng::GetInstance().GetModel(path);
}