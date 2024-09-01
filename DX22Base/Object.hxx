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

class GameObject;

class Object
{
public:
	Object* GetParent()const { return m_pParent; }
	Object* GetRootObject() { return (m_pParent ? m_pParent->GetRootObject() : this); }

	void AddChild(Object* pChild) { m_Children.push_back(pChild); };

protected:
	Object();
	virtual ~Object();

	GameObject MakeObject();
	void UpdateChildren();
	void Delete();
	void RemoveChild(Object*);

	virtual void Update() = 0;

	bool m_IsActive;

	Object* m_pParent;
	std::deque<Object*> m_Children;

private:
};

#endif // !_____Object_HXX_____