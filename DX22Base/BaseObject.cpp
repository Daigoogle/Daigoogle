#include "BaseObject.h"


BaseObject::BaseObject()
	:m_pInstance(nullptr)
{

}

BaseObject::~BaseObject()
{

}

void BaseObject::SetInstance(BaseObjectInstance* pInstance)
{
	m_pInstance = pInstance;
}

bool BaseObject::IsNull()
{
	return (m_pInstance == nullptr) ? true : false ;
}

const int BaseObject::GetID()
{
	if (m_pInstance == nullptr)
		return -1;
	return m_pInstance->GetID();
}

void BaseObject::SetID(int nID)
{
	if (m_pInstance == nullptr)
		return;
	m_pInstance->SetID(nID);
}

const int BaseObject::GetTag()
{
	if (m_pInstance == nullptr)
		return -1;
	return m_pInstance->GetTag();
}

void BaseObject::SetTag(int nTagNo)
{
	if (m_pInstance == nullptr)
		return ;
	m_pInstance->SetTag(nTagNo);
}

void BaseObject::SetTag(std::string strTagName)
{
	if (m_pInstance == nullptr)
		return;
	m_pInstance->SetTag(strTagName);
}

const bool BaseObject::IsActive()
{
	if (m_pInstance == nullptr)
		return false;
	return m_pInstance->IsActive();
}

void BaseObject::SetActive(bool bIsActive)
{
	if (m_pInstance == nullptr)
		return;
	m_pInstance->SetActive(bIsActive);
}

const bool BaseObject::IsStopUpdate()
{
	if (m_pInstance == nullptr)
		return false;
	return m_pInstance->IsStopUpdate();
}

void BaseObject::SetStopUpdate(bool bStopUpdate)
{
	if (m_pInstance == nullptr)
		return;
	m_pInstance->SetStopUpdate(bStopUpdate);
}

BaseObject BaseObject::GetParent()
{
	if (m_pInstance == nullptr)
		return BaseObject();
	BaseObject parentObj;
	parentObj.SetInstance(m_pInstance->GetParent());
	return parentObj;
}

const std::string BaseObject::GetName()
{
	if (m_pInstance == nullptr)
		return nullptr;
	return m_pInstance->GetName();
}

void BaseObject::SetName(std::string sName)
{
	if (m_pInstance == nullptr)
		return;
	m_pInstance->SetName(sName);
}

void BaseObject::AddChild(BaseObject& pChild)
{
	if (m_pInstance == nullptr)
		return;
	m_pInstance->AddChild(pChild.m_pInstance);
}

void BaseObject::RemoveChild(BaseObject& pChild)
{
	if (m_pInstance == nullptr)
		return;
	m_pInstance->RemoveChild(pChild.m_pInstance);
}

SceneBase* BaseObject::GetScene()
{
	if (m_pInstance == nullptr)
		return nullptr;
	return m_pInstance->GetScene();
}