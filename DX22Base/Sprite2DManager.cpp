#include "Sprite2DManager.h"
#include "DirectX11SetUp.h"
// ----------�ÓI�����o�錾----------
const float	Sprite2DManager::NEAR_CLIP = 0.0f;
const float	Sprite2DManager::FAR_CLIP = 1.0f;

Sprite2DManager::Sprite2DManager()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

Sprite2DManager::~Sprite2DManager()
{
	UnInit();
}

bool	Sprite2DManager::Init(void)
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
	m_meshBuffer = std::make_unique<MeshBuffer>(desc);

	SetWindowSize();

	return true;
}

void Sprite2DManager::Draw(void)
{
	// �[�x�o�b�t�@��؂�
	DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();

	RenderTarget* pRT = Dx11.GetDefaultRTV();//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDS = Dx11.GetDefaultDSV();//DepthStencilView�̎擾


	//	z���Ń\�[�g
	std::vector<Sprite2DComponent*> SortDate;
	while (!m_queue.empty())
	{
		SortDate.push_back(m_queue.front());
		int InsertNo = 0;
		//for (int i = 0; i < SortDate.size(); i++)
		//{
		//	float back_z = SortDate.back()->GetTransform()->GetWorldPosition().z;
		//	float i_z = SortDate[i]->GetTransform()->GetWorldPosition().z;
		//	if (back_z > i_z)
		//	{
		//		auto Date = SortDate.back();
		//		SortDate.back() = SortDate[i];
		//		SortDate[i] = Date;
		//		break;
		//	}
		//}
		m_queue.pop();
	}

	for (int i = 1; i < SortDate.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			float i_z = SortDate[i]->GetTransform()->GetWorldPosition().z;
			float j_z = SortDate[j]->GetTransform()->GetWorldPosition().z;
			if (i_z < j_z)
			{
				auto Date = SortDate[j];
				SortDate[j] = SortDate[i];
				SortDate[i] = Date;
			}
		}
	}

	for (auto& Value : SortDate)
	{
		m_queue.push(Value);
	}

	Dx11.SetRenderTargets(1, &pRT, nullptr);
	
	// ----------�`��R���|�[�l���g�����o�����[�v----------
	while (!m_queue.empty())
	{
		// �R���|�[�l���g�̎��o��
		Sprite2DComponent* pComp = m_queue.front();
		m_queue.pop();

		// �g�����X�t�H�[�����擾
		Transform* pTransform = pComp->GetTransform();

		// �p�����[�^���擾
		DirectX::XMFLOAT4X4	vertexMats[2];
		vertexMats[0] = pTransform->GetWorldMatrix();
		VertexShader* pVtxShader = pComp->GetVertexShader();
		PixelShader* pPixelShader = pComp->GetPixelShader();
		fVec4		color = pComp->GetColor();
		fVec2		uvOffset = pComp->GetUVOffset();
		fVec2		uvScale = pComp->GetUVScale();
		std::vector<std::shared_ptr<char[]>>& vtxShaderData = pComp->GetVertexShaderWriteData();
		std::vector<std::shared_ptr<char[]>>& pixelShaderData = pComp->GetPixelShaderWriteData();
		Texture* pTexture = pComp->GetTexture();

		// �v���W�F�N�V�����s��̏���
		DirectX::XMStoreFloat4x4(&vertexMats[1],
			DirectX::XMMatrixOrthographicLH(
				1.0f, 1.0f, NEAR_CLIP, FAR_CLIP
			)
		);

		// ���_�V�F�[�_�̏���
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

		pVtxShader->WriteBuffer(0, &vertexMats);	//�s�����������
		pVtxShader->WriteBuffer(1, afVtxInfos);		//UV����������
		int nNoInfo = 2;
		for (int nCntInfo = 0; nCntInfo < vtxShaderData.size(); nCntInfo++)
		{
			pVtxShader->WriteBuffer(nNoInfo, vtxShaderData[nCntInfo].get());
			nNoInfo++;
		}
		pVtxShader->Bind();

		// �s�N�Z���V�F�[�_�̏���
		for (int nCntInfo = 0; nCntInfo < pixelShaderData.size(); nCntInfo++)
		{
			pPixelShader->WriteBuffer(nCntInfo, pixelShaderData[nCntInfo].get());
		}
		pPixelShader->SetTexture(0, pTexture);
		pPixelShader->Bind();

		// ���b�V���o�b�t�@�̏���
		m_meshBuffer->Draw();
	}

	Dx11.SetRenderTargets(1, &pRT, pDS);// �[�x�o�b�t�@��߂�
}

void Sprite2DManager::UnInit(void)
{

}

void Sprite2DManager::AddQueue(Sprite2DComponent* pComp)
{
	m_queue.push(pComp);
}

void Sprite2DManager::SetWindowSize()
{
	nVec2 BufferSize = Singleton<DirectX11SetUp>::GetInstance().GetBufferSize();
	m_windowSize = { static_cast<float>(BufferSize.x),static_cast<float>(BufferSize.y) };
}