#include "GameObject.hxx"
#include "DebugRestriction.hxx"

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

bool GameObject::IsNull() const
{
	if (m_pInstance)
		return true;
	return false;
}

void GameObject::AddChild(GameObject& pChild)
{
	NullptrCheck_void_(m_pInstance)
	pChild.m_pInstance->m_pParent = m_pInstance;
	m_pInstance->m_childs.push_back(pChild.m_pInstance);
}

void GameObject::RemoveChild(GameObject& pChild)
{
	NullptrCheck_void_(m_pInstance)
	pChild.m_pInstance->m_pParent = nullptr;
	m_pInstance->m_childs.remove(pChild.m_pInstance);
}

const bool GameObject::IsActive()
{
	NullptrCheck_void_(m_pInstance)
	return m_pInstance->IsActive();
}

void GameObject::SetActive(bool isActive)
{
	NullptrCheck_void_(m_pInstance)
	m_pInstance->m_IsActive = isActive;
}

const unsigned __int64 GameObject::GetID()
{
	NullptrCheck_void_(m_pInstance)
	return m_pInstance->m_ObjectID;
}

void GameObject::SetName(const std::string& name)
{
	NullptrCheck_void_(m_pInstance)
	m_pInstance->m_Name = name;
}

const std::string& GameObject::GetName()
{
	NullptrCheck_void_(m_pInstance)
	return m_pInstance->m_Name;
}

GameObject GameObject::GetParent()
{
	NullptrCheck_void_(m_pInstance)
	GameObject Parentobj(m_pInstance->m_pParent);
	return Parentobj;
}

unsigned GameObject::GetTag()
{
	NullptrCheck_void_(m_pInstance)
	return m_pInstance->m_Tag;	
}

void GameObject::SetTag(unsigned tag)
{
	NullptrCheck_void_(m_pInstance)
	m_pInstance->m_Tag = tag;
}

SceneBase* GameObject::GetScene()
{
	NullptrCheck_void_(m_pInstance)
	return m_pInstance->m_pScene;
}

Transform& GameObject::GetTransform()
{
	NullptrCheck_void_(m_pInstance)
	return m_pInstance->m_Transform;
}