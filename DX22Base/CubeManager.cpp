#include "CubeManager.h"
#include "CameraManager.h"

CubeManager::CubeManager()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

CubeManager::~CubeManager()
{
	UnInit();
}

bool CubeManager::Init()
{
	// ���f�[�^�� 
	Vertex vtx[] = {
		//-z��
		{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ 0.5f, 0.5f,-0.5f},{1.0f,0.0f}},//1
		{{-0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//2
		{{ 0.5f,-0.5f,-0.5f},{1.0f,1.0f}},//3
		//z
		{{-0.5f, 0.5f,0.5f},{0.0f,0.0f}},//4
		{{ 0.5f, 0.5f,0.5f},{1.0f,0.0f}},//5
		{{-0.5f,-0.5f,0.5f},{0.0f,1.0f}},//6
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//7
		//-x
		{{ -0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ -0.5f, 0.5f,0.5f},{1.0f,0.0f}},//4
		{{ -0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//2
		{{ -0.5f,-0.5f,0.5f},{1.0f,1.0f}},//6
		//x
		{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//1
		{{ 0.5f, 0.5f,0.5f},{1.0f,0.0f}},//5
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//3
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//7
		//-y
		{{ -0.5f, -0.5f,-0.5f},{0.0f,0.0f}},//2
		{{ -0.5f, -0.5f,0.5f},{1.0f,0.0f}},//6
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//3
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//5

		//y
		{{ -0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ -0.5f, 0.5f,0.5f},{1.0f,0.0f}},//4
		{{ 0.5f,0.5f,-0.5f},{0.0f,1.0f}},//1
		{{ 0.5f,0.5f,0.5f},{1.0f,1.0f}},//5
	};

	int idx[] = {
		0,1,2,		1,3,2,		//-Z��
		6,5,4,		6,7,5,		//Z��
		10,9,0,		10,11,9,	//-x
		12,13,14,	13,15,14,	//x
		18,17,16,	18,19,17,	//-y
		0,21,22,	21,23,22,	//y

	};
	// �o�b�t�@�̍쐬
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

void CubeManager::Draw()
{
	CameraBase* Camm = CameraManager::GetInstance().GetMainCamera();
	while (!m_queue.empty())
	{
		// �f�[�^�̎��o��
		CubeComponent* pSpriteComp = m_queue.front();
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
			}
			pPixelShader->SetTexture(0, pTexture);
			pPixelShader->Bind();

			// ���b�V���o�b�t�@
			m_MeshBuffer->Draw();
	}
}

void CubeManager::UnInit()
{
	m_MeshBuffer.release();
	
}

void CubeManager::AddQueue(CubeComponent* pComp)
{
	m_queue.push(pComp);
}