#include "ThreadPool.hxx"
#include "ThreadPoolMng.hxx"

ThreadPool::ThreadPool()
	: IsEnd(false)
	, EndCompleat(false)
{

}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::PoolLoop()
{
	while (!IsEnd) 
	{
		ThreadPoolMng::GetInstance().GetPoolFead()();
	}
	EndCompleat = true;
}