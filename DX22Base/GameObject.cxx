#include "GameObject.hxx"


GameObject::GameObject()
	: m_pInstance(nullptr)
{

}

GameObject::GameObject(GameObjectInst* pInstance)
	: m_pInstance(pInstance)
{

}

GameObject::~GameObject()
{

}

void GameObject::SetInstance(GameObjectInst* pInstance)
{
	m_pInstance = pInstance;
}

bool GameObject::IsNull() const
{
	if (m_pInstance)
		return true;
	return false;
}

void GameObject::AddChild(GameObject& pChild)
{
	if(!m_pInstance)
		return;
	pChild.m_pInstance->m_pParent = m_pInstance;
	m_pInstance->m_childs.push_back(pChild.m_pInstance);
}

void GameObject::RemoveChild(GameObject& pChild)
{
	if(!m_pInstance)
		return;
	pChild.m_pInstance->m_pParent = nullptr;
	m_pInstance->m_childs.remove(pChild.m_pInstance);
}

const bool GameObject::IsActive()
{
	if (!m_pInstance)
		return false;
	return m_pInstance->IsActive();
}

void GameObject::SetActive(bool isActive)
{
	if (m_pInstance)
		m_pInstance->m_IsActive = isActive;
}

const unsigned __int64 GameObject::GetID()
{
	if(!m_pInstance)
		return 0;
	return m_pInstance->m_ObjectID;
}

void GameObject::SetName(const std::string& name)
{
	if (m_pInstance)
		m_pInstance->m_Name = name;
}

const std::string& GameObject::GetName()
{
	if (m_pInstance)
		return m_pInstance->m_Name;
	static std::string str = "";
	return str;
}

GameObject GameObject::GetParent()
{
	if (!m_pInstance)
		return GameObject();
	GameObject Parentobj;
	Parentobj.SetInstance(m_pInstance->m_pParent);
	return Parentobj;
}

unsigned GameObject::GetTag()
{
	if (!m_pInstance)
		return 0;
	return m_pInstance->m_Tag;	
}

void GameObject::SetTag(unsigned tag)
{
	if (m_pInstance)
		m_pInstance->m_Tag = tag;
}

SceneBase* GameObject::GetScene()
{
	if (!m_pInstance)
		return nullptr;
	return m_pInstance->m_pScene;
}