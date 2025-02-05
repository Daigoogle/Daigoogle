#include "Component.hxx"

#include "DebugRestriction.hxx"
#include "GameObject.hxx"

GameObject* Component::GetGameObject()
{
	return
#ifdef _DEBUG
		NullptrCheck(dynamic_cast<GameObject*>(m_pBaseObject));
#else
		static_cast<GameObject*>(m_pBaseObject);
#endif // _DEBUG
}