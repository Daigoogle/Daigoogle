#include "ThreadPoolMng.hxx"

ThreadPoolMng::ThreadPoolMng()
	: Singleton(UPDATE_ORDER::NO_UPDATE)	
{

}

ThreadPoolMng::~ThreadPoolMng()
{

}

void ThreadPoolMng::AddPool(std::function<void()> _func)
{
	m_Pool.push(_func);
}

/// @brief 
/// @return 
std::function<void()> ThreadPoolMng::GetPoolFead()
{
	if(m_Pool.empty())
		return nullptr;
	std::function<void()> func = m_Pool.front();
	m_Pool.pop();
	return func;
}