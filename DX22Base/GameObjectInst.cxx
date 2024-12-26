#include "GameObjectInst.hxx"
#include "Component.hxx"

uint32 GameObjectInst::ms_ObjectID = 0;

GameObjectInst::GameObjectInst()
	: m_Name("Nameless")
	, m_Tag(0)
	, m_IsDelete(false)
	, m_ObjectID(ms_ObjectID++)
{

}

GameObjectInst::~GameObjectInst()
{
	m_Components.clear();
}

bool GameObjectInst::Init()
{
	for (auto& elem : m_Components)
		FalseCheck(elem->Init());// ‰Šú‰»
	return true;// ‰Šú‰»¬Œ÷
}

void GameObjectInst::Update()
{
	if (!IsActive())
		return;
	for (auto& elem : m_Components)
		elem->Update();// XV
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