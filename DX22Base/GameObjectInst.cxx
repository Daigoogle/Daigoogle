#include "GameObjectInst.hxx"
#include "Component.hxx"

uint32 GameObjectInst::ms_ObjectID = 0;

GameObjectInst::GameObjectInst()
	: m_Name("Nameless")
	, m_Tag(0)
	, m_IsActive(true)
	, m_IsDelete(false)
	, m_ObjectID(ms_ObjectID++)
	, m_pParent(nullptr)
	, m_pScene(nullptr)
{

}

GameObjectInst::~GameObjectInst()
{
	//for (auto& elem:m_Components)
	//	elem.release();
	m_Components.clear();
}

bool GameObjectInst::Init()
{
	for (auto& elem : m_Components)
		FalseCheck(elem->Init());// 初期化
	return true;// 初期化成功
}

void GameObjectInst::Update()
{
	if (!IsActive())
		return;
	for (auto& elem : m_Components)
		elem->Update();// 更新
	m_Transform.Update();
}

const bool GameObjectInst::IsActive()
{
	return m_IsActive && (m_pParent ? m_pParent->IsActive() : true);
}

void GameObjectInst::Delete()
{
	m_IsDelete = true;
}