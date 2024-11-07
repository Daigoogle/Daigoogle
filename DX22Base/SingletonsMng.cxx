#include "SingletonsMng.hxx"

std::array<std::deque<_SingletonBase*>, static_cast<int>(UPDATE_ORDER::LAST_UPDATE) + 1> Supervision::m_Updaters;//更新処理
std::stack<void(*)()> Supervision::m_finalizers;//終了処理


namespace 
{
	std::mutex gMutex;// 排他制御用
}

/// @brief コンストラクタ
_SingletonBase::_SingletonBase(UPDATE_ORDER Order)
{
	Supervision::addUpdater(this, Order);// 更新処理を追加
}

/// @brief 終了処理を保存
/// @param func 終了処理
void Supervision::addFinalizer(void(*func)())
{
	std::lock_guard<std::mutex> lock(gMutex);// 排他制御
	m_finalizers.push(func);// 終了処理を追加
}

/// @brief 更新処理を保存
/// @param pSingleton 処理するシングルトン
/// @param order 更新順
void Supervision::addUpdater(_SingletonBase* pSingleton, UPDATE_ORDER order)
{
	if(order == UPDATE_ORDER::NO_UPDATE)// 更新しない場合は追加しない
		return;
	m_Updaters[static_cast<int>(order)].push_back(pSingleton);// 更新処理を追加
}

/// @brief 更新処理を行う
void Supervision::Updater()
{
	for (auto& updaters : m_Updaters)// 更新処理を順番に実行
		for (auto& updater : updaters)
			updater->Update();// 更新処理を実行
}

/// @brief 終了処理を行う
void Supervision::Finalize()
{
	std::lock_guard<std::mutex> lock(gMutex);// 排他制御
	for (auto& elem : m_Updaters)// 更新処理をクリア
		elem.clear();
	while (!m_finalizers.empty()){// 終了処理を逆順に実行
		m_finalizers.top()();
		m_finalizers.pop();
	}
}