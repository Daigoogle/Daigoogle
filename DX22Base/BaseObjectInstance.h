//	=-=-= インクルードガード部 =-=-=
#ifndef _____BASE_OBJECT_INSTANCE_H_____
#define _____BASE_OBJECT_INSTANCE_H_____

//	=-=-= インクルード部 =-=-=
#include <memory>
#include <vector>
#include <list>
#include <string>

#include "Component.h"
#include "SceneBase.h"

class BaseObjectInstance
{
public:
	BaseObjectInstance();
	BaseObjectInstance(const BaseObjectInstance&);
	BaseObjectInstance& operator=(const BaseObjectInstance&) = delete;
	BaseObjectInstance& operator=(BaseObjectInstance&&) = delete;
	~BaseObjectInstance();

	void Init();
	void Update();
	void UnInit();

	template<typename TypeComponent>
	TypeComponent* AddComponent()
	{
		std::unique_ptr<Component> pComponent(static_cast<Component*>(new TypeComponent()));
		m_Components.emplace_back(move(pComponent));
		Component* pAddComponent = m_Components.back().get();
		pAddComponent->SetBaseObject(this);

		return dynamic_cast<TypeComponent*>(pAddComponent);
	}

	template<typename TypeComponent>
	TypeComponent* GetComponent()
	{
		for (auto& Value : m_Components)
		{
			Component* pComp = Value.get();
			TypeComponent* pTypeComponent = dynamic_cast<TypeComponent*>(pComp);

			if (pTypeComponent != nullptr)
			{
				return pTypeComponent;
			}
		}
		return nullptr;
	}

	const int GetID();
	void SetID(int nID);
	const int GetTag();
	void SetTag(int nTagNo);
	void SetTag(std::string strTagName);
	const bool IsActive();
	void SetActive(bool bIsActive);
	const bool IsStopUpdate();
	void SetStopUpdate(bool bStopUpdate);
	BaseObjectInstance* GetParent();
	const std::string GetName();
	void SetName(std::string sName);
	void AddChild(BaseObjectInstance* pChild);
	void RemoveChild(BaseObjectInstance* pChild);
	SceneBase* GetScene();
	void SetScene(SceneBase* pScene);

private:
	int								m_nID;
	int								m_nTag;
	std::string							m_strName;
	char							m_cObjStatus;
	std::vector<std::unique_ptr<Component>>	m_Components;
	std::list<BaseObjectInstance*>		m_childs;
	BaseObjectInstance*				m_pParent;
	SceneBase*						m_pScene;

	static const char _IS_NO_UPDATE_FLG		= 0b00010000;
	static const char _IS_ACTIVE_FLG	= 0b00000101;
};

#endif // !_____BASE_OBJECT_INSTANCE_H_____