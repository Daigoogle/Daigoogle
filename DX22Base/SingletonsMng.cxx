#include "SingletonsMng.hxx"

std::array<std::deque<_SingletonBase*>, static_cast<int>(UPDATE_ORDER::LAST_UPDATE) + 1> Supervision::m_Updaters;//�X�V����
std::deque<void(*)()> Supervision::m_finalizers;//�I������

namespace 
{
	std::mutex gMutex;// �r������p
}

/// @brief �R���X�g���N�^
_SingletonBase::_SingletonBase(UPDATE_ORDER Order)
{
	Supervision::addUpdater(this, Order);// �X�V������ǉ�
}

/// @brief �I��������ۑ�
/// @param func �I������
void Supervision::addFinalizer(void(*func)())
{
	std::lock_guard<std::mutex> lock(gMutex);// �r������
	m_finalizers.push_back(func);// �I��������ǉ�
}

/// @brief �X�V������ۑ�
/// @param pSingleton ��������V���O���g��
/// @param order �X�V��
void Supervision::addUpdater(_SingletonBase* pSingleton, UPDATE_ORDER order)
{
	if(order == UPDATE_ORDER::NO_UPDATE)// �X�V���Ȃ��ꍇ�͒ǉ����Ȃ�
		return;
	m_Updaters[static_cast<int>(order)].push_back(pSingleton);// �X�V������ǉ�
}

/// @brief �X�V�������s��
void Supervision::Updater()
{
	for (auto& updaters : m_Updaters)// �X�V���������ԂɎ��s
		for (auto& updater : updaters)
			updater->Update();// �X�V���������s
}

/// @brief �I���������s��
void Supervision::Finalize()
{
	std::lock_guard<std::mutex> lock(gMutex);// �r������
	for (auto& elem : m_Updaters)// �X�V�������N���A
		elem.clear();
	while (!m_finalizers.empty()){// �I���������t���Ɏ��s
		m_finalizers.back()();
		m_finalizers.pop_back();
	}
}