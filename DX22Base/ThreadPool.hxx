//	ファイル名	：ThreadPool.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/08/25 22:57:02
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____ThreadPool_HXX_____
#define _____ThreadPool_HXX_____

// =-=-= インクルード部 =-=-=
#include <thread>
#include <memory>

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void Start();

	void PoolLoop();
private:
	std::unique_ptr<std::thread> m_Thread;
	bool m_IsEnd;
	bool m_EndCompleat;
};

#endif // !_____ThreadPool_HXX_____