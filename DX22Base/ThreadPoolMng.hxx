//	ファイル名	：ThreadPoolMng.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/08/25 22:56:47
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____ThreadPoolMng_HXX_____
#define _____ThreadPoolMng_HXX_____

// =-=-= インクルード部 =-=-=
#include "SingletonsMng.hxx"
#include <vector>
#include <thread>
#include <shared_mutex>
#include <functional>
#include <queue>

class ThreadPoolMng :public Singleton<ThreadPoolMng>
{
	friend class Singleton<ThreadPoolMng>;
public:
	ThreadPoolMng();
	~ThreadPoolMng();
	
	void AddPool(std::function<void()>);
	std::function<void()> GetPoolFead();
private:
	std::shared_mutex m_Mutex;
	std::vector<std::thread> m_Thread;
	std::queue<std::function<void()>> m_Pool;
};

#endif // !_____ThreadPoolMng_HXX_____