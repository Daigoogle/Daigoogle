#include "ThreadPool.hxx"
#include "ThreadPoolMng.hxx"

#include <thread>
#include <functional>

ThreadPool::ThreadPool()
	: m_IsEnd(false)
	, m_EndCompleat(false)
{}

ThreadPool::~ThreadPool()
{
	m_IsEnd = true;
	m_Thread->join();
}

void ThreadPool::Start()
{
	m_Thread = std::make_unique<std::thread>([this]() {this->PoolLoop(); });
}

void ThreadPool::PoolLoop()
{
	std::function<void()> func;
	while (true) {
		func = ThreadPoolMng::GetInstance().GetPoolFead();
		if (func)func();
		if (m_IsEnd)break;
	}
	m_EndCompleat = true;
}