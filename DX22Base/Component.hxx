//	ファイル名	：Component.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/16 9:43:49
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Component_HXX_____
#define _____Component_HXX_____

#include "GameObject.hxx"
#include "SceneBase.hxx"

class Component
{
	friend class GameObject;
	friend class SceneBase;
public:
	Component():m_pBaseObject(nullptr){};
	virtual ~Component() {}

	virtual bool Init() = 0;
	virtual void Update() = 0;

	/// @brief GameObjectを取得する
	/// @brief 注意※SceneComponentの場合エラー
	/// @return 所属ゲームオブジェクト
	GameObject* GetGameObject();
private:
	Object* m_pBaseObject;
};

#endif // !_____Component_HXX_____