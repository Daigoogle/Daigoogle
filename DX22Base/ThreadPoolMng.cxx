#include "ThreadPoolMng.hxx"
#include <thread>

ThreadPoolMng::ThreadPoolMng()
	: Singleton(UPDATE_ORDER::NO_UPDATE)	
{

}

ThreadPoolMng::~ThreadPoolMng()
{

}

bool ThreadPoolMng::Init()
{
	for (unsigned i = 0; 
		//i < static_cast<unsigned>(std::thread::hardware_concurrency() * 0.25f)
		i < 1
		; i++) {
		m_ThreadClass.push_back(std::make_unique<ThreadPool>());
		m_ThreadClass.back()->Start();
	}

	return true;
}

void ThreadPoolMng::AddPool(std::function<void()> _func)
{
	m_Pool.push(_func);
}

/// @brief 
/// @return 
std::function<void()> ThreadPoolMng::GetPoolFead()
{
	std::unique_lock<std::shared_mutex> lock(m_Mutex);
	if(m_Pool.empty())
		return nullptr;
	std::function<void()> func = m_Pool.front();
	m_Pool.pop();
	return func;
}