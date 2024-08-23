#include "Sprite3DManager.h"
#include "CameraBase.h"
#include "Transform.h"
#include "CameraManager.h"

Sprite3DManager::Sprite3DManager()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

Sprite3DManager::~Sprite3DManager()
{
	UnInit();
}

bool Sprite3DManager::Init()
{
	// ----------���b�V���o�b�t�@�̏�����----------
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};

	Vertex vtx[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {1.0f, 1.0f}},
	};

	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_MeshBuffer = std::make_unique<MeshBuffer>(desc);
	return true;
}

void Sprite3DManager::Draw()
{
	CameraBase* Camm = Singleton<CameraManager>::GetInstance().GetMainCamera();

	while (!m_queue.empty())
	{
		// �f�[�^�̎��o��
		Sprite3DComponent* pSpriteComp = m_queue.front();
		m_queue.pop();

		// �g�����X�t�H�[�����擾
		Transform* pTransform = pSpriteComp->GetTransform();

		// �p�����[�^�̎��o��
		VertexShader* pVtxShader = pSpriteComp->GetVertexShader();
		PixelShader* pPixelShader = pSpriteComp->GetPixelShader();
		fVec4 color = pSpriteComp->GetColor();
		fVec2 uvOffset = pSpriteComp->GetUVOffset();
		fVec2 uvScale = pSpriteComp->GetUVScale();
		std::vector<std::shared_ptr<char[]>>& vtxShaderData = pSpriteComp->GetVertexShaderWriteData();
		std::vector<std::shared_ptr<char[]>>& pixelShaderData = pSpriteComp->GetPixelShaderWriteData();

		std::map<UINT, Texture*> textures = pSpriteComp->GetTexture();

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

		// ���[���h�s��̎��o��
		DirectX::XMFLOAT4X4 mat[3];
		mat[0] = pTransform->GetWorldMatrix();

		// �J�����̃f�[�^�����o�����[�v
		//CCameraManager& camManager = CameraManager::GetInstance();

			// �J�����̍s��̎��o��
		mat[1] = Camm->GetViewMatrix();
		mat[2] = Camm->GetProjMatrix();

		// ���_�V�F�[�_�ւ̏������ݏ���
		pVtxShader->WriteBuffer(0, mat);
		pVtxShader->WriteBuffer(1, afVtxInfos);
		int nNoInfo = 2;
		for (int nCntInfo = 0; nCntInfo < vtxShaderData.size(); nCntInfo++)
		{
			pVtxShader->WriteBuffer(nNoInfo, vtxShaderData[nCntInfo].get());
			nNoInfo++;
		}
		pVtxShader->Bind();

		// �s�N�Z���V�F�[�_�ւ̏������ݏ���
		for (int nCntInfo = 0; nCntInfo < pixelShaderData.size(); nCntInfo++)
		{
			pPixelShader->WriteBuffer(nCntInfo, pixelShaderData[nCntInfo].get());
			float a = *pixelShaderData[nCntInfo].get();
			int i = 0;
		}

		for(auto& elem: textures)
			pPixelShader->SetTexture(elem.first, elem.second);

		pPixelShader->Bind();

		// ���b�V���o�b�t�@
		m_MeshBuffer->Draw();
	}
}
void Sprite3DManager::UnInit()
{

}
void Sprite3DManager::AddQueue(Sprite3DComponent* pComp)
{
	m_queue.push(pComp);
}