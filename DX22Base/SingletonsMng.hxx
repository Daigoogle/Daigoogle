//	�t�@�C����	�FSingletonsMng.hxx
//	  �T  �v		�FMozc�����x�[�X�Ƃ����V���O���g�����Ǘ�����N���X
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/09 20:37:20
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SingletonsMng_HXX_____
#define _____SingletonsMng_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include <array>
#include <deque>
#include <stack>
#include <mutex>
#include <functional>
#include <type_traits>

// =-=-= �萔��`�� =-=-=
enum class UPDATE_ORDER {
	NO_UPDATE = -1,	//�X�V���Ȃ�
	FIRST_UPDATE,	//�P�ԂɍX�V
	SECOND_UPDATE,	//�Q�ԂɍX�V
	THIRD_UPDATE,	//�R�ԂɍX�V
	LAST_UPDATE		//�Ō�ɍX�V
};

/// @brief �V���O���g���̊��N���X
class _SingletonBase
{
public:	
	/// @brief ���������� ���I�[�o�[���C�h���Ă�������
	virtual bool Init() { return true; };
	/// @brief �X�V���� ���I�[�o�[���C�h���Ă�������
	virtual void Update() {};

protected:
	/// @brief �R���X�g���N�^���֎~
	_SingletonBase() = delete;
	/// @brief �R���X�g���N�^
	_SingletonBase(UPDATE_ORDER Order);
	/// @brief �f�X�g���N�^
	virtual ~_SingletonBase() {};
};

/// @brief �V���O���g���̍ŏI�������s���N���X
class Supervision final
{
	template<typename Type> friend class Singleton;
	friend _SingletonBase;
public:
	/// @brief �������������s��
	/// @return ����������true
	static bool Initialize();
	/// @brief �X�V�������s��
	static void Updater();
	/// @brief �I���������s��
	static void Finalize();

private:
	/// @brief �I��������ǉ�����
	/// @param func �I������
	static void addFinalizer(void(*func)());
	/// @brief �X�V������ǉ�����
	/// @param pSingleton ��������V���O���g��
	/// @param order �X�V��
	static void addUpdater(_SingletonBase* pSingleton, UPDATE_ORDER order);

private:
	static std::array<std::deque<_SingletonBase*>, static_cast<int>(UPDATE_ORDER::LAST_UPDATE) + 1> m_Updaters;//�X�V����
	static std::stack<void(*)()> m_finalizers;//�I������
};

/// @brief �V���O���g���̃C���X�^���X�𐶐��E�ێ�����N���X
template<typename Type>
class Singleton :public _SingletonBase
{
public:
	using getInst = Type & (*)();
	/// @brief �C���X�^���X���擾���� ���񐄏�
	/// @return �C���X�^���X
	static inline Type& __CreateInstance()
	{
		//���߂ČĂяo���ꂽ�Ȃ�C���X�^���X�̐���
		std::call_once(initFlag, Create);
		return *instance;
	}

	/// @brief �C���X�^���X���擾���� ���񐄏�
	/// @return �C���X�^���X
	static inline Type& __GetInstance()
	{
		return *instance;
	}

	/// @brief �ÓI�ŃR���X�g�Ȋ֐��|�C���^�̎Q��
	static const std::function<Type&(void)>& GetInstance;
private:
	static std::function<Type&(void)> _GetInstfuncP;

	/// @brief �C���X�^���X�𐶐�����
	static void Create()
	{
		instance = New(Type);
		_GetInstfuncP = __GetInstance;
		Supervision::addFinalizer(&Singleton<Type>::destroy);
	}

	/// @brief �C���X�^���X��j������
	static void destroy()
	{
		DebugString_(typeid(Type).name() + std::string(" �I�������J�n   ===== �l�l�l \n"))
		delete instance;
		instance = nullptr;
		DebugString_(typeid(Type).name() + std::string(" �I�������I��� ===== �x�x�x \n"))
	}

	static std::once_flag initFlag;	//��������̃t���O(�r������)
	static Type* instance;			//����̃C���X�^���X

protected:

	/// @brief �R���X�g���N�^���֎~
	Singleton() = delete;
	/// @brief �R���X�g���N�^
	Singleton(UPDATE_ORDER Order) :_SingletonBase(Order) {}
	/// @brief �f�X�g���N�^
	virtual ~Singleton() = default;

	// �R�s�[�E����֎~
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};
// �ÓI�����o���`
template <typename Type> std::once_flag Singleton<Type>::initFlag;
template <typename Type> Type* Singleton<Type>::instance = nullptr;
template <typename Type> const std::function<Type& (void)>& Singleton<Type>::GetInstance = Singleton<Type>::_GetInstfuncP;
template <typename Type> std::function<Type& (void)> Singleton<Type>::_GetInstfuncP = Singleton<Type>::__CreateInstance;

#endif // !_____SingletonsMng_HXX_____