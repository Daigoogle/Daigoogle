#include "Component.hxx"

#include "GameObject.hxx"

GameObject Component::GetGameObject()
{
	return GameObject(m_pGameObjectInst);
}