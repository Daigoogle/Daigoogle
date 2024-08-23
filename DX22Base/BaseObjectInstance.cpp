#include "BaseObjectInstance.h"
#include "Component.h"
#include "TagManager.h"

BaseObjectInstance::BaseObjectInstance()
	:m_nID(-1)
	, m_nTag(-1)
	, m_cObjStatus(_IS_ACTIVE_FLG)
	, m_pParent(nullptr)
	, m_pScene(nullptr)
{

}

BaseObjectInstance::BaseObjectInstance(const BaseObjectInstance&)
	:m_nID(-1)
	, m_nTag(-1)
	, m_cObjStatus(_IS_ACTIVE_FLG)
	, m_pParent(nullptr)
	, m_pScene(nullptr)
{

}

BaseObjectInstance::~BaseObjectInstance()
{
	UnInit();
}

void BaseObjectInstance::Init()
{
	for (auto& Value : m_Components)
		Value.get()->Init();
}

void BaseObjectInstance::Update()
{
	if (!IsActive())
		return;

	for (auto& Value : m_Components)
	{
		Value.get()->Update();
	}
}

void BaseObjectInstance::UnInit()
{
	for (auto& Value : m_Components)
		Value.get()->UnInit();
}

const int BaseObjectInstance::GetID()
{
	return m_nID;
}

void BaseObjectInstance::SetID(int nID)
{
	m_nID = nID;
}

const int BaseObjectInstance::GetTag()
{
	return m_nTag;
}

void BaseObjectInstance::SetTag(int nTagNo)
{
	m_nTag = nTagNo;
}

void BaseObjectInstance::SetTag(std::string strTagName)
{
	m_nTag = TagManager::GetInstance().AddTag(strTagName);
}

const bool	BaseObjectInstance::IsActive()
{
	if (m_pParent != nullptr)
	{
		if (!m_pParent->IsActive())
			return false;
	}
	return (m_cObjStatus & _IS_ACTIVE_FLG) ? true : false;
}

void BaseObjectInstance::SetActive(bool bIsActive)
{
	m_cObjStatus &= ~_IS_ACTIVE_FLG;
	m_cObjStatus |= bIsActive * _IS_ACTIVE_FLG;
}

const bool BaseObjectInstance::IsStopUpdate()
{
	if (m_pParent != nullptr)
		if (m_pParent->IsStopUpdate())
			return true;
	return (m_cObjStatus & _IS_NO_UPDATE_FLG) ? true : false;
}

void BaseObjectInstance::SetStopUpdate(bool bStopUpdate)
{
	m_cObjStatus &= ~_IS_NO_UPDATE_FLG;
	m_cObjStatus |= bStopUpdate * _IS_NO_UPDATE_FLG;
}

BaseObjectInstance* BaseObjectInstance::GetParent()
{
	return m_pParent;
}

const std::string BaseObjectInstance::GetName()
{
	return m_strName;
}

void BaseObjectInstance::SetName(std::string sName)
{
	m_strName = sName;
}

void BaseObjectInstance::AddChild(BaseObjectInstance* pChild)
{
	pChild->m_pParent = this;
	m_childs.push_back(pChild);
}

void BaseObjectInstance::RemoveChild(BaseObjectInstance* pChild)
{
	pChild->m_pParent = nullptr;
	m_childs.remove(pChild);
}

SceneBase* BaseObjectInstance::GetScene()
{
	return m_pScene;
}

void BaseObjectInstance::SetScene(SceneBase* pScene)
{
	m_pScene = pScene;
}
