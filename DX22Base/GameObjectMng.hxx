//	ファイル名	：GameObjectMng.hxx
//	  概  要 	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/16 11:24:35
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____GameObjectMng_HXX_____
#define _____GameObjectMng_HXX_____

// =-=-= インクルード部 =-=-=
#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>

#include "SingletonsMng.hxx"

class GameObjectInst;
class GameObject;
class SceneBase;

class GameObjectMng: public Singleton<GameObjectMng>
{
	friend class Singleton<GameObjectMng>;
public:
	/// @brief 初期化処理
	/// @return 成功したらtrue
	bool Init() override;
	/// @brief 更新処理
	void Update() override;

	/// @brief オブジェクトの作成
	/// @param pScene 作成するオブジェクトの所属シーン
	/// @return 作成したオブジェクト
	GameObject MakeObject(SceneBase* pScene);

	/// @brief シーンのオブジェクトの解放
	/// @param pScene 解放するシーン
	void DeleteSceneObjects(SceneBase* pScene);

private:
	/// @brief コンストラクタ
	GameObjectMng();
	/// @brief デストラクタ
	~GameObjectMng();

	/// @brief 生成オブジェクトの初期化と登録
	void InitObjects();
	/// @brief 現シーンのオブジェクトの更新
	/// @param pScene 現在のシーン
	void UpdateObjects(SceneBase* pScene);

	void DeleteObject();

	/// @brief オブジェクトのロードキュー
	std::unordered_map<SceneBase* ,std::queue<GameObjectInst*>> m_ObjectsLoadQueue;
	/// @brief オブジェクトの更新キュー
	std::unordered_map<SceneBase* , std::vector<GameObjectInst*>> m_ObjectsQueue;
	/// @brief 削除するオブジェクトのキュー
	std::unordered_map<ID,SceneBase*> m_ObjectsDeleteQueue;
};

#endif // !_____GameObjectMng_HXX_____