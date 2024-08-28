#include "ThreadPool.hxx"
#include "ThreadPoolMng.hxx"

ThreadPool::ThreadPool()
	: m_IsEnd(false)
	, m_EndCompleat(false)
{

}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::PoolLoop()
{
	while (!m_IsEnd) 
	{
		ThreadPoolMng::GetInstance().GetPoolFead()();
	}
	m_EndCompleat = true;
}