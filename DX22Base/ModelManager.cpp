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
    //----------カメラマネージャーを取得----------
    CameraBase* camManager = CameraManager::GetInstance().GetMainCamera();
    // カメラのビュー行列を取得
    DirectX::XMFLOAT4X4 viewMatrix = camManager->GetViewMatrix();
    DirectX::XMFLOAT4X4 projMatrix = camManager->GetProjMatrix();
    fVec3 camPos = { camManager->GetPos().x,camManager->GetPos().y,camManager->GetPos().z };

    //fVec3 lightPos = pLightComp->GetPosition();// 光源の座標を取得

    // 描画コンポーネントを取り出す
    for (auto modelComp : m_modelQueue)
    {
        // 描画コンポーネントからトランスフォームを取得
        Transform* pModelTransform = modelComp->GetTransform();
        if (pModelTransform == nullptr)
        {
            continue;
        }

        // 描画コンポーネントからモデルポインタを取得
        Model* pModel = modelComp->GetModel(); //std::move(modelComp->GetModel());
        if (pModel == nullptr)
        {
            continue;
        }

        float alp = modelComp->GetAlpha();

        // 描画コンポーネントから頂点シェーダーを取得
        //Shader* pVertexShader = modelComp->GetVertex();// = (std::move(modelComp->GetVertex()) != nullptr) ? (std::move(modelComp->GetVertex())) : m_vertexShader.get();

        // 描画コンポーネントからピクセルシェーダーを取得
        //Shader* pPixelShader = modelComp->GetPixel();// = (std::move(modelComp->GetPixel()) != nullptr) ? (std::move(modelComp->GetPixel())) : m_pixelShader.get();
        VertexShader* pVertexShader = modelComp->GetVertexShader();
        PixelShader* pPixelShader = modelComp->GetPixelShader();

        pModel->SetVertexShader(pVertexShader);
        pModel->SetPixelShader(pPixelShader);

        // 描画コンポーネントからワールド行列を取得
        DirectX::XMFLOAT4X4 worldMatrix = pModelTransform->GetWorldMatrix();

        // 頂点シェーダに渡すバッファを作成
        //DirectX::XMVECTOR   light = DirectX::XMVector3Normalize(DirectX::XMVectorSet(lightPos.x, lightPos.y, lightPos.z, 1.0f));
        //m_posCBuf.world = worldMatrix;
        //m_posCBuf.view = viewMatrix;
        //m_posCBuf.projection = projMatrix;

        // 頂点シェーダを配列に格納
        DirectX::XMFLOAT4X4 aWVP[3];
        aWVP[0] = worldMatrix;
        aWVP[1] = viewMatrix;
        aWVP[2] = projMatrix;

        //DirectX::XMStoreFloat4(&m_ligCBuf.sourcePos, light);

        // 描画
        //pModel->SetVertexShader(dynamic_cast<VertexShader*>(pVertexShader));
        //pModel->SetPixelShader(dynamic_cast<PixelShader*>(pPixelShader));
        //pVertexShader->WriteBuffer(0, &m_posCBuf);
        //pVertexShader->Bind();
        //pPixelShader->WriteBuffer(0, &m_ligCBuf);
        //pPixelShader->Bind();
        //pModel->Draw();

        // アニメ用にモデルを書き込み

        // ワールド、ビュー、プロジェクション行列を書き込み
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

        // カメラ
        lightInfo.eyePos.x = camPos.x;
        lightInfo.eyePos.y = camPos.y;
        lightInfo.eyePos.z = camPos.z;

        // ライトの方向
        lightInfo.lightDirection.x = lightDir.x;
        lightInfo.lightDirection.y = lightDir.y;
        lightInfo.lightDirection.z = lightDir.z;

        // α
        lightInfo.alpha = alp;

        pPixelShader->WriteBuffer(0, &lightInfo);

        //ポイントライトの情報を書き込み
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
                // この計算はゲームつくろー「スキンメッシュの仕組み」が参考になる
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
