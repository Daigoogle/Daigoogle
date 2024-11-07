#include "ThreadPool.hxx"
#include <thread>

namespace{
	bool ThreadContinue = false;
	void poolloop(){
		std::function<void()> func;
		while (ThreadContinue) {
			func = ThreadPool::GetInstance().GetPoolFead();
			if (func)func();
		}
	}
}

#define _THREADPOOL_

ThreadPool::ThreadPool()
#ifdef _THREADPOOL_
	: Singleton(UPDATE_ORDER::NO_UPDATE)
{
	ThreadContinue = true;
	m_ThreadCount = static_cast<uint16>(std::thread::hardware_concurrency() * 0.13f);
	for (uint16 i = 0; i < m_ThreadCount; i++) {
		m_Thread.push_back(std::make_unique<std::thread>(poolloop));
	}
}
#else
	: Singleton(UPDATE_ORDER::LAST_UPDATE){}
#endif // _THREADPOOL_  

ThreadPool::~ThreadPool()
{
	ThreadContinue = false;
	for (auto& elem : m_Thread)
		elem->join();
	DebugString_("スレッド数：" + std::to_string(m_ThreadCount) + "\n")
}

bool ThreadPool::Init()
{
	return true;
}

void ThreadPool::Update()
{
#ifndef _THREADPOOL_
	while (!m_Pool.empty())
	{
		m_Pool.front()();
		m_Pool.pop();
	}
#endif // _THREADPOOL_
}

void ThreadPool::AddPool(std::function<void()> _func)
{
	m_Pool.push(_func);
}

/// @brief 
/// @return
std::function<void()> ThreadPool::GetPoolFead()
{
	std::unique_lock<std::shared_mutex> lock(m_Mutex);
	if(m_Pool.empty())
		return nullptr;
	std::function<void()> func = m_Pool.front();
	m_Pool.pop();
	return func;
}
