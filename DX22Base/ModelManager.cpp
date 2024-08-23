#include "ModelManager.h"
#include "CameraManager.h"
#include "BaseObject.h"

ModelManager::ModelManager()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

ModelManager::~ModelManager()
{
	UnInit();
}

bool ModelManager::Init()
{
	return true;
}

void ModelManager::Update()
{

}

void ModelManager::Draw()
{
    //----------�J�����}�l�[�W���[���擾----------
    CameraBase* camManager = CameraManager::GetInstance().GetMainCamera();
    // �J�����̃r���[�s����擾
    DirectX::XMFLOAT4X4 viewMatrix = camManager->GetViewMatrix();
    DirectX::XMFLOAT4X4 projMatrix = camManager->GetProjMatrix();
    fVec3 camPos = { camManager->GetPos().x,camManager->GetPos().y,camManager->GetPos().z };

    //fVec3 lightPos = pLightComp->GetPosition();// �����̍��W���擾

    // �`��R���|�[�l���g�����o��
    for (auto modelComp : m_modelQueue)
    {
        // �`��R���|�[�l���g����g�����X�t�H�[�����擾
        Transform* pModelTransform = modelComp->GetTransform();
        if (pModelTransform == nullptr)
        {
            continue;
        }

        // �`��R���|�[�l���g���烂�f���|�C���^���擾
        Model* pModel = modelComp->GetModel(); //std::move(modelComp->GetModel());
        if (pModel == nullptr)
        {
            continue;
        }

        float alp = modelComp->GetAlpha();

        // �`��R���|�[�l���g���璸�_�V�F�[�_�[���擾
        //Shader* pVertexShader = modelComp->GetVertex();// = (std::move(modelComp->GetVertex()) != nullptr) ? (std::move(modelComp->GetVertex())) : m_vertexShader.get();

        // �`��R���|�[�l���g����s�N�Z���V�F�[�_�[���擾
        //Shader* pPixelShader = modelComp->GetPixel();// = (std::move(modelComp->GetPixel()) != nullptr) ? (std::move(modelComp->GetPixel())) : m_pixelShader.get();
        VertexShader* pVertexShader = modelComp->GetVertexShader();
        PixelShader* pPixelShader = modelComp->GetPixelShader();

        pModel->SetVertexShader(pVertexShader);
        pModel->SetPixelShader(pPixelShader);

        // �`��R���|�[�l���g���烏�[���h�s����擾
        DirectX::XMFLOAT4X4 worldMatrix = pModelTransform->GetWorldMatrix();

        // ���_�V�F�[�_�ɓn���o�b�t�@���쐬
        //DirectX::XMVECTOR   light = DirectX::XMVector3Normalize(DirectX::XMVectorSet(lightPos.x, lightPos.y, lightPos.z, 1.0f));
        //m_posCBuf.world = worldMatrix;
        //m_posCBuf.view = viewMatrix;
        //m_posCBuf.projection = projMatrix;

        // ���_�V�F�[�_��z��Ɋi�[
        DirectX::XMFLOAT4X4 aWVP[3];
        aWVP[0] = worldMatrix;
        aWVP[1] = viewMatrix;
        aWVP[2] = projMatrix;

        //DirectX::XMStoreFloat4(&m_ligCBuf.sourcePos, light);

        // �`��
        //pModel->SetVertexShader(dynamic_cast<VertexShader*>(pVertexShader));
        //pModel->SetPixelShader(dynamic_cast<PixelShader*>(pPixelShader));
        //pVertexShader->WriteBuffer(0, &m_posCBuf);
        //pVertexShader->Bind();
        //pPixelShader->WriteBuffer(0, &m_ligCBuf);
        //pPixelShader->Bind();
        //pModel->Draw();

        // �A�j���p�Ƀ��f������������

        // ���[���h�A�r���[�A�v���W�F�N�V�����s�����������
        //ShaderList::SetWVP(aWVP);
        pVertexShader->WriteBuffer(0, aWVP);

        fVec3 lightDir = {1.0f, -1.0f, -1.0f};
        //lightDir = Vector3Calc::Normal(lightDir);

        struct DirectionLight
        {
            DirectX::XMFLOAT3 lightDirection = { 0.0f,0.0f,0.0f };
            float pad1;
            DirectX::XMFLOAT3 lightColor = { 1.0f,1.0f,1.0f };
            float pad2;
            DirectX::XMFLOAT3 eyePos = {};
            float pad3;
            float alpha;
            DirectX::XMFLOAT3 pad4;
            /*
            DirectX::XMFLOAT4 dummy1 = {0.0f,0.0f,0.0f,0.0f};
            DirectX::XMFLOAT3 dummy2 = {0.0f,0.0f,0.0f};
            */
        }lightInfo;

        // �J����
        lightInfo.eyePos.x = camPos.x;
        lightInfo.eyePos.y = camPos.y;
        lightInfo.eyePos.z = camPos.z;

        // ���C�g�̕���
        lightInfo.lightDirection.x = lightDir.x;
        lightInfo.lightDirection.y = lightDir.y;
        lightInfo.lightDirection.z = lightDir.z;

        // ��
        lightInfo.alpha = alp;

        pPixelShader->WriteBuffer(0, &lightInfo);

        //�|�C���g���C�g�̏�����������
        //pPixelShader->WriteBuffer(1, &m_ligCBuf);
        //pPixelShader->Bind();

        pModel->Draw(nullptr, [this, pModel, pVertexShader, pPixelShader](int index)
        {
            const Model::Mesh* pMesh = pModel->GetMesh(index);
            const Model::Material* pMaterial = pModel->GetMaterial(pMesh->materialID);
            //ShaderList::SetMaterial(*pMaterial);
            pPixelShader->SetTexture(0, pMaterial->pTexture);

            DirectX::XMFLOAT4X4 bones[200];
            for (int i = 0; i < pMesh->bones.size() && i < 200; ++i)
            {
                // ���̌v�Z�̓Q�[������[�u�X�L�����b�V���̎d�g�݁v���Q�l�ɂȂ�
                DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
                    pMesh->bones[i].invOffset *
                    pModel->GetBone(pMesh->bones[i].index)
                ));
            }
            //ShaderList::SetBones(bones);
            pVertexShader->WriteBuffer(1, bones);
        });
    }
    m_modelQueue.clear();
}

void ModelManager::UnInit()
{
	
}

void ModelManager::AddQueue(ModelComponent* comp)
{
	//m_queue.push(comp);
    m_modelQueue.push_back(comp);
}
