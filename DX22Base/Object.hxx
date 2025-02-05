//	�t�@�C����	�FObject.hxx
//	  �T  �v		�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/08/30 0:04:49
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Object_HXX_____
#define _____Object_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include <deque>
#include "Location.hxx"

class Object : virtual protected Location
{
	friend class SceneManager;
public:
	Object* GetParent()const;
	void AddChild(Object* pChild); 
	
	template <typename TypeObject, typename = std::enable_if_t<std::is_base_of_v<Object, TypeObject>>>
	TypeObject& thisCreateObject() {
		TypeObject* pObject = new TypeObject();
		this->AddChild(pObject);
		SceneManager::GetInstance().m_InitQueue.push(pObject);
		return *pObject;
	}

	virtual bool Init() = 0;
	virtual void Update() = 0;
	
	void Delete();
	void RemoveChild(Object*);

	bool IsActive()const;
	void SetActive(bool IsActive);

	const ID GetID();

protected:
	Object();
	virtual ~Object();

	void UpdateChildren();

private:
	bool m_IsActive;
	unique_ID m_ID;
	Object* m_pParent;
	std::deque<Object*> m_Children;
};

#endif // !_____Object_HXX_____