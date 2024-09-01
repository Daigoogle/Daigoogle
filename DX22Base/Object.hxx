//	ファイル名	：Object.hxx
//	  概  要		：
//	作	成	者	：daigo
//	 作成日時	：2024/08/30 0:04:49
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Object_HXX_____
#define _____Object_HXX_____

// =-=-= インクルード部 =-=-=
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