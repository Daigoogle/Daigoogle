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
#include "GameObjectInst.hxx"

class GameObject
{
public:
	GameObject();
	GameObject(GameObjectInst* pInstance);
	~GameObject();

	bool IsNull() const;

	/// @brief コンポーネントの追加
	/// @tparam TypeComp 追加するコンポーネントの型
	/// @return 追加したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* AddComponent()
	{
		if (!m_pInstance)
			return nullptr;
		return m_pInstance->AddComponent<TypeComp>();
	}

	/// @brief コンポーネントの取得
	/// @tparam TypeComp 取得するコンポーネントの型
	/// @return 取得したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* GetComponent()
	{
		if (!m_pInstance)
			return nullptr;
		return m_pInstance->GetComponent<TypeComp>();
	}

	/// @brief 子オブジェクトを追加
	/// @param pChild 追加する子オブジェクト
	void AddChild(GameObject& pChild);
	/// @brief 子オブジェクトを分離
	/// @param pChild 分離する子オブジェクト
	void RemoveChild(GameObject& pChild);

	/// @brief 有効かどうか
	/// @return 有効ならtrue
	const bool IsActive();
	/// @brief 有効かどうかを設定
	/// @param isActive 有効にするならtrue
	void SetActive(bool isActive);
	/// @brief IDの取得
	/// @return ID
	const unsigned __int64 GetID();
	/// @brief 名前の設定
	/// @param name 設定する名前
	void SetName(const std::string& name);
	/// @brief 名前の取得
	/// @return 名前
	const std::string& GetName();
	/// @brief 親オブジェクトの取得
	/// @return 親オブジェクト
	GameObject GetParent();
	/// @brief タグの取得
	/// @return タグ
	unsigned GetTag();
	/// @brief タグの設定
	/// @param tag 設定するタグ
	void SetTag(unsigned tag);
	/// @brief シーンの取得
	/// @return シーン
	SceneBase* GetScene();
private:
	GameObjectInst* m_pInstance;// 実体
};

#endif // !_____GameObject_HXX_____