#include "Component.h"
#include "BaseObject.h"

BaseObject Component::GetBaseObject()
{
	BaseObject obj;
	obj.SetInstance(m_pSelfInstance);
	return obj;
}
void Component::SetBaseObject(BaseObjectInstance* pInstance)
{
	m_pSelfInstance = pInstance;
}