//	ファイル名	：GameObject.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/16 11:24:03
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____GameObject_HXX_____
#define _____GameObject_HXX_____

// =-=-= インクルード部 =-=-=
#include <type_traits>
#include <deque> 
#include <memory>
#include "Object.hxx"
#include "Transform.hxx"
#include "DebugRestriction.hxx"

class Component;

class GameObject : public Object, private Transform
{
public:
	GameObject();
	~GameObject();

	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	/// @brief コンポーネントの追加
	/// @tparam TypeComp 追加するコンポーネントの型
	/// @return 追加したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* AddComponent()
	{
		std::unique_ptr<TypeComp> pComp(New(TypeComp));
		pComp->m_pBaseObject = this;
		m_Components.push_back(std::move(pComp));
		return static_cast<TypeComp*>(m_Components.back().get());
	}

	/// @brief コンポーネントの取得
	/// @tparam TypeComp 取得するコンポーネントの型
	/// @return 取得したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
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

	/// @brief 名前の設定
	/// @param name 設定する名前
	void SetName(const std::string& name);
	/// @brief 名前の取得
	/// @return 名前
	const std::string& GetName();
	/// @brief タグの取得
	/// @return タグ
	unsigned GetTag();
	/// @brief タグの設定
	/// @param tag 設定するタグ
	void SetTag(unsigned tag);
	/// @brief Transformの取得
	/// @return Transform
	Transform* GetTransform();

	virtual bool Init()override;
	virtual void Update()override;
private:
	Name m_Name;						// オブジェクト名
	unsigned m_Tag;						// タグ
	std::deque<std::unique_ptr<Component>> m_Components;	// 追加されたコンポーネント
};

#endif // !_____GameObject_HXX_____