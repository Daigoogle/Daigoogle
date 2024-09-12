#include "GameObjectMng.hxx"
#include "GameObjectInst.hxx"
#include "GameObject.hxx"
#include "SceneMng.hxx"
#include "SceneBase.hxx"

GameObjectMng::GameObjectMng()
	: Singleton(UPDATE_ORDER::THIRD_UPDATE)
{

}

GameObjectMng::~GameObjectMng()
{
	for (auto& elem : m_ObjectsLoadQueue){
		while (!elem.second.empty()){
			delete elem.second.front();
			elem.second.pop();
		}
	}
	for (auto& elem : m_ObjectsQueue) {
		while (!elem.second.empty()){
			delete elem.second.back();
			elem.second.pop_back();
		}
	}
		
	m_ObjectsDeleteQueue.clear();
}

bool GameObjectMng::Init()
{
	return true;
}

void GameObjectMng::Update()
{
	InitObjects();// まずは初期化
	DeleteObject();// 不要物の削除
	UpdateObjects(SceneMng::GetInstance().GetNowScene());// 更新
}

void GameObjectMng::InitObjects()
{
	// キューの中身を全て初期化
	for (auto& elem: m_ObjectsLoadQueue){
		while (!elem.second.empty()){
			 elem.second.front()->Init();
			 m_ObjectsQueue[elem.first].push_back(elem.second.front());// InitからUpdateに移動
			 elem.second.pop();
		}
	}
}

void GameObjectMng::UpdateObjects(SceneBase* pScene)
{
	if (!pScene)return;
	// シーンキューの中身を更新
	//while (m_ObjectsQueue[pScene].empty())
	//	m_ObjectsQueue[pScene].front()->Update();
	for (auto& elem:m_ObjectsQueue[pScene]){
		elem->Update();
		if (elem->m_IsDelete) {
			m_ObjectsDeleteQueue[elem->m_ObjectID] = elem->m_pScene;
		}
	}
}

void GameObjectMng::DeleteSceneObjects(SceneBase* pScene)
{
	for(auto& elem : m_ObjectsQueue[pScene])
		delete elem;
	m_ObjectsQueue.erase(pScene);
}

GameObject GameObjectMng::MakeObject(SceneBase* pScene)
{
	GameObjectInst* pInst = new GameObjectInst;// インスタンスの生成
	pInst->m_pScene = pScene;		// シーンの設定
	GameObject obj(pInst);	// インスタンスを設定
	m_ObjectsLoadQueue[pScene].push(pInst);// キューに追加
	return obj;
}

/// @brief オブジェクトの削除
void GameObjectMng::DeleteObject()
{
	std::unordered_map<SceneBase*,int> bisection;// 昇順に処理するため、以前の探索範囲を記憶
	for (auto& elem : m_ObjectsDeleteQueue) {
		uint32_t id = elem.first;
		SceneBase* pScene = elem.second;
		int Right = (int)m_ObjectsQueue[pScene].size() - 1; // 探索範囲の右端
		int& mid = bisection[pScene]; // 前回の探索値を取得
		int Left = mid;	// 探索範囲の左端
		mid = static_cast<int>( (Right - mid) * 0.5f + mid); // 中央値の初期化

		// 二分探索
		while (true) {	
			if (m_ObjectsQueue[pScene][mid]->m_ObjectID < id) {
				Left = mid;
				mid = static_cast<int>((Right + Left) * 0.5f);
			}
			else if (m_ObjectsQueue[pScene][mid]->m_ObjectID > id) {
				Right = mid;
				mid = static_cast<int>((Right + Left) * 0.5f);
			}
			else {
				m_ObjectsQueue[pScene].erase(m_ObjectsQueue[pScene].begin() + mid);
				break;
			}
			if (Right - 1 == Left) {
				if(m_ObjectsQueue[pScene][Right]->m_ObjectID == id)
					m_ObjectsQueue[pScene].erase(m_ObjectsQueue[pScene].begin() + Right);
				else if(m_ObjectsQueue[pScene][Left]->m_ObjectID == id)
					m_ObjectsQueue[pScene].erase(m_ObjectsQueue[pScene].begin() + Left);
				break;
			}
		}
	}
	m_ObjectsDeleteQueue.clear();
}
