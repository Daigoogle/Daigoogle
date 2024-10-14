#include "ThreadPoolMng.hxx"
#include <thread>

#define _THREADPOOL_

ThreadPoolMng::ThreadPoolMng()
	: Singleton(
#ifdef _THREADPOOL_
		UPDATE_ORDER::NO_UPDATE
#else
		UPDATE_ORDER::LAST_UPDATE
#endif // _THREADPOOL_
	)	
{
#ifdef _THREADPOOL_
	m_ThreadCount = static_cast<uint16>(std::thread::hardware_concurrency() * 0.13f);
	for (uint16 i = 0;i < m_ThreadCount; i++) {
		m_ThreadClass.push_back(std::make_unique<ThreadPool>());
		m_ThreadClass.back()->Start();
	}                              
#endif // _THREADPOOL_
}

ThreadPoolMng::~ThreadPoolMng()
{
	DebugString_("スレッド数：" + std::to_string(m_ThreadCount) + "\n")
}

bool ThreadPoolMng::Init()
{
	return true;
}

void ThreadPoolMng::Update()
{
#ifndef _THREADPOOL_
	while (!m_Pool.empty())
	{
		m_Pool.front()();
		m_Pool.pop();
	}
#endif // _THREADPOOL_
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