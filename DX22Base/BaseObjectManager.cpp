#include "BaseObjectManager.h"
#include "SceneBase.h"
#include "Transform.h"

int BaseObjectManager::ms_nLastGenerateLoadID = -1;
int BaseObjectManager::ms_nLastGenerateMainID = -1;

BaseObjectManager::BaseObjectManager()
	: Singleton(UPDATE_ORDER::SECOND_UPDATE)
	, m_Mode(ProcessMode::MainScene)
{

}

BaseObjectManager::~BaseObjectManager()
{
	UnInit();
}

bool BaseObjectManager::BaseObjectManager::Init()
{
	return true;
}

void BaseObjectManager::BaseObjectManager::Update()
{
	switch (m_Mode)
	{
	case BaseObjectManager::ProcessMode::MainScene:
		InitMainObjects();
		UpdateMainObjects();
		break;
	case BaseObjectManager::ProcessMode::LoadScene:
		InitLoadObjects();
		UpdateLoadObjects();
		break;
	case BaseObjectManager::ProcessMode::_Max:
		break;
	default:
		break;
	}
}

void BaseObjectManager::BaseObjectManager::UnInit()
{
	DeleteMainObject();
	DeleteLoadObject();
}

BaseObject BaseObjectManager::Make(SceneBase* pScene)
{
	// ----------オブジェクトの作成----------
	std::unique_ptr<BaseObjectInstance> newObj = std::make_unique<BaseObjectInstance>();
	newObj->SetScene(pScene);

	BaseObjectInstance* pObjInstance = nullptr;
	if (pScene->GetIsLoadScene())
	{
		//ロードシーンへロード
		m_LoadObjects.push_back(std::move(newObj));
		pObjInstance = m_LoadObjects.back().get();	//オブジェクトのポインタを取得

		// ----------初期化リストに追加----------
		m_InitLoadObjQueue.push(pObjInstance);

		// ----------IDを設定----------
		pObjInstance->SetID(ms_nLastGenerateLoadID + 1);	//IDを設定
		ms_nLastGenerateLoadID += 1;						//最後に生成したIDを更新
	}
	else
	{
		// メインのシーンへロード
		m_MainObjects.push_back(std::move(newObj));
		pObjInstance = m_MainObjects.back().get();	//オブジェクトのポインタを取得

		// ----------初期化リストに追加----------
		m_InitMainObjQueue.push(pObjInstance);

		// ----------IDを設定----------
		pObjInstance->SetID(ms_nLastGenerateMainID + 1);	//IDを設定
		ms_nLastGenerateMainID += 1;						//最後に生成したIDを更新
	}

	// ----------参照を作成----------
	BaseObject obj;						//オブジェクトの参照を作成
	obj.SetInstance(pObjInstance);			//実体を設定

	// ---------- デフォルトコンポーネント ----------
	pObjInstance->AddComponent<Transform>();

	return obj;
}

void BaseObjectManager::SetMode(BaseObjectManager::ProcessMode mode)
{
	m_Mode = mode;
}

BaseObjectManager::ProcessMode BaseObjectManager::GetMode()
{
	return m_Mode;
}

void BaseObjectManager::DeleteMainObject()
{
	m_MainObjects.clear();

	while (!m_InitMainObjQueue.empty())
	{
		m_InitMainObjQueue.pop();
	}

	ResetFirstMainID();
}

void BaseObjectManager::DeleteLoadObject()
{
	m_LoadObjects.clear();

	while (!m_InitLoadObjQueue.empty())
	{
		m_InitLoadObjQueue.pop();
	}

	ResetFirstLoadID();
}

void BaseObjectManager::InitMainObjects()
{
	while (!m_InitMainObjQueue.empty())
	{
		m_InitMainObjQueue.front()->Init();
		m_InitMainObjQueue.pop();
	}
}

void BaseObjectManager::ResetFirstMainID()
{
	ms_nLastGenerateMainID = -1;
}

void BaseObjectManager::ResetFirstLoadID()
{
	ms_nLastGenerateLoadID = -1;
}

void BaseObjectManager::InitLoadObjects()
{
	while (!m_InitLoadObjQueue.empty())
	{
		m_InitLoadObjQueue.front()->Init();
		m_InitLoadObjQueue.pop();
	}
}

void BaseObjectManager::UpdateMainObjects()
{
	for (auto& Value : m_MainObjects)
		Value.get()->Update();
}

void BaseObjectManager::UpdateLoadObjects()
{
	for (auto& Value : m_LoadObjects)
		Value.get()->Update();
}

BaseObject ObjectManager::Make(SceneBase* pScene)
{
	return Singleton<BaseObjectManager>::GetInstance().Make(pScene);
}