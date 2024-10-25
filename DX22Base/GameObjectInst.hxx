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
#include "GameObjectMng.hxx"
#include "Transform.hxx"
#include "DebugRestriction.hxx"

class Component;

class GameObjectInst
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
		pComp->m_GameObject = GameObject(this);
		m_Components.push_back(std::move(pComp));
		return static_cast<TypeComp*>(m_Components.back().get());
	}

	template<typename TypeComp>
	TypeComp* GetComponent()
	{
		for (const auto elem : m_Components)
		{
			if (typeid(TypeComp) == typeid(elem.get()))
				return elem.get();
		}
		DebugBreakPoint_
		return nullptr;
	}

	void Delete();

private:
	static ID ms_ObjectID;

	Name m_Name;					// オブジェクト名
	unsigned m_Tag;						// タグ
	bool m_IsActive;					// アクティブかどうか
	bool m_IsDelete;					// このオブジェクトの削除フラグ
	std::list<std::unique_ptr<Component>> m_Components;	// 追加されたコンポーネント
	ID m_ObjectID;					// オブジェクトID
	std::list<GameObjectInst*> m_childs;// 子オブジェクト群
	GameObjectInst* m_pParent;			// 親オブジェクト
	SceneBase* m_pScene;				// 所属シーン

	Transform m_Transform;				// トランスフォーム
};

#endif // !_____GameObjectInst_HXX_____