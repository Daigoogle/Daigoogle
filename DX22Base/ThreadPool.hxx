//	�t�@�C����	�FThreadPool.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/08/25 22:57:02
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____ThreadPool_HXX_____
#define _____ThreadPool_HXX_____

// =-=-= �C���N���[�h�� =-=-=


class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void PoolLoop();
private:
	bool m_IsEnd;
	bool m_EndCompleat;
};

#endif // !_____ThreadPool_HXX_____