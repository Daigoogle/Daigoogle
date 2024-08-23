#include "ModelComponent.h"
#include "ModelManager.h"
#include "ModelRegister.h"
#include "ShaderList.h"
#include "BaseObject.h"
#include "Main.h"
#include "PutLog.h"

ModelComponent::ModelComponent()
	: m_fAlpha(1.0f)
	, m_pModel(nullptr)
	, m_PS(nullptr),m_VS(nullptr)
	, m_Transform(nullptr)
	, m_Models()
{
	
}

ModelComponent::~ModelComponent()
{
	UnInit();
}

void ModelComponent::Init()
{
	m_Transform = GetBaseObject().GetComponent<Transform>();
	if (m_Transform == nullptr)
		Error("Is Null : Transform\n at ModelComponent");

	if (m_PS == nullptr)
		m_PS = Singleton<ShaderList>::GetInstance().LoadPixelShader("Assets/Shader/DefaltModel_PS.cso");
	if (m_VS == nullptr)
		m_VS = Singleton<ShaderList>::GetInstance().LoadVertexShader("Assets/Shader/DefaltModel_VS.cso");
}

void ModelComponent::Update()
{
	// モデルの秒数を更新
	if (m_pModel != nullptr)
	{
		m_pModel->Step(GetTick());
		Singleton<ModelManager>::GetInstance().AddQueue(this);
	}
}

void ModelComponent::UnInit()
{

}

Transform* ModelComponent::GetTransform()
{
	return m_Transform;
}

Model* ModelComponent::GetModel()
{
	return m_pModel;
}

void ModelComponent::RegisterModel(int nModelNo, std::string sPath, bool bIsAnime)
{
	// 領域を追加
	m_Models.push_back(tModelData());

	size_t modelSize = m_Models.size();
	tModelData& rModel = m_Models[modelSize - 1];

	// モデル番号の設定
	rModel.nModelNo = nModelNo;

	// モデルの読込
	rModel.pModel = Singleton<ModelRegister>::GetInstance().LoadModel(sPath);

	// アニメの読込
	if (bIsAnime)
	{
		rModel.animeNo = rModel.pModel->AddAnimation(sPath.c_str());
		SelectModelWithAnime(nModelNo, true, 1.0f);
	}
	else
	{
		SelectModel(nModelNo);
	}
}

void ModelComponent::SelectModel(int nModelNo)
{
	// モデルを選択
	tModelData& rModel = SearchModelByNo(nModelNo);

	m_pModel = rModel.pModel;
}

void ModelComponent::SelectModelWithAnime(int nModelNo, bool bIsLoop, float fSpeed)
{
	// モデルを選択
	tModelData& rModel = SearchModelByNo(nModelNo);

	m_pModel = rModel.pModel;

	m_pModel->Play(rModel.animeNo, bIsLoop, fSpeed);
}

void ModelComponent::SetAlpha(float alpha)
{
	m_fAlpha = alpha;
}

float ModelComponent::GetAlpha()
{
	return m_fAlpha;
}

ModelComponent::tModelData& ModelComponent::SearchModelByNo(int nModelNo)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < m_Models.size(); nCntModel++)
	{
		if (nModelNo == m_Models[nCntModel].nModelNo)
		{
			break;
		}
	}
	return m_Models[nCntModel];
}

void ModelComponent::LoadPixelShader(std::string sPath)
{
	m_PS = Singleton<ShaderList>::GetInstance().LoadPixelShader(sPath);
}

void ModelComponent::LoadVertexShader(std::string sPath)
{
	m_VS = Singleton<ShaderList>::GetInstance().LoadVertexShader(sPath);
}

PixelShader* ModelComponent::GetPixelShader()
{
	return m_PS;
}

VertexShader* ModelComponent::GetVertexShader()
{
	return m_VS;
}
