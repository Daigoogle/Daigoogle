//	�t�@�C����	�FThreadPoolMng.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/08/25 22:56:47
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____ThreadPoolMng_HXX_____
#define _____ThreadPoolMng_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "SingletonsMng.hxx"
#include <vector>
#include <shared_mutex>
#include <functional>
#include <queue>

#include "ThreadPool.hxx"

class ThreadPoolMng :public Singleton<ThreadPoolMng>
{
	friend class Singleton<ThreadPoolMng>;
public:
	bool Init() override;
	void Update() override;

	void AddPool(std::function<void()>);
	std::function<void()> GetPoolFead();

private:
	ThreadPoolMng();
	~ThreadPoolMng();

private:
	uint16 m_ThreadCount;

	std::shared_mutex m_Mutex;
	std::vector<std::unique_ptr<ThreadPool>> m_ThreadClass;
	std::queue<std::function<void()>> m_Pool;
};

#endif // !_____ThreadPoolMng_HXX_____