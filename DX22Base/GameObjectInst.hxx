//	ファイル名	：GameObjectInst.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/16 11:52:00
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____GameObjectInst_HXX_____
#define _____GameObjectInst_HXX_____

// =-=-= インクルード部 =-=-=
#include <list>
#include <string>
#include <memory>
#include "Object.hxx"
#include "Transform.hxx"
#include "GameObjectMng.hxx"

class Component;
class Object;

class GameObjectInst :public Object
{
	friend class GameObjectMng;
	friend class GameObject;
private:
	GameObjectInst();
	~GameObjectInst();

	GameObjectInst& operator=(const GameObjectInst&) = delete;
	GameObjectInst& operator=(GameObjectInst&&) = delete;

	bool Init();
	void Update();

	const bool IsActive();

	template<typename TypeComp>
	TypeComp* AddComponent()
	{
		std::unique_ptr<TypeComp> pComp(new TypeComp);
		pComp->m_pGameObjectInst = this;
		m_Components.push_back(std::move(pComp));
		return pComp.get();
	}

	template<typename TypeComp>
	TypeComp* GetComponent()
	{
		for (const auto elem : m_Components)
		{
			TypeComp* pComp = dynamic_cast<TypeComp*>(elem.get());
			if (pComp != nullptr)
				return pComp;
		}
		return nullptr;
	}

	void Delete();

private:
	static uint32_t ms_ObjectID;

	std::string m_Name;					// 名前
	unsigned m_Tag;						// タグ
	bool m_IsDelete;					// 削除フラグ
	std::list<std::unique_ptr<Component>> m_Components;	// コンポーネント
	uint32_t m_ObjectID;		// ID

	bool m_IsFollowParent;				// 親に追従するかどうか

	Transform m_Transform;				// 位置情報
};

#endif // !_____GameObjectInst_HXX_____