//	�t�@�C����	�FGameObject.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/16 11:24:03
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____GameObject_HXX_____
#define _____GameObject_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include <type_traits>
#include <deque> 
#include <memory>
#include "Object.hxx"
#include "Transform.hxx"
#include "DebugRestriction.hxx"

class Component;

class GameObject : public Object, private Transform
{
public:
	GameObject();
	~GameObject();

	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	/// @brief �R���|�[�l���g�̒ǉ�
	/// @tparam TypeComp �ǉ�����R���|�[�l���g�̌^
	/// @return �ǉ������R���|�[�l���g�̃|�C���^
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* AddComponent()
	{
		std::unique_ptr<TypeComp> pComp(New(TypeComp));
		pComp->m_pBaseObject = this;
		m_Components.push_back(std::move(pComp));
		return static_cast<TypeComp*>(m_Components.back().get());
	}

	/// @brief �R���|�[�l���g�̎擾
	/// @tparam TypeComp �擾����R���|�[�l���g�̌^
	/// @return �擾�����R���|�[�l���g�̃|�C���^
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* GetComponent()
	{
		for (const auto elem : m_Components)
		{
			if (typeid(TypeComp) == typeid(elem.get()))
				return elem.get();
		}
		DebugBreakPoint_
		return nullptr;
	}

	/// @brief ���O�̐ݒ�
	/// @param name �ݒ肷�閼�O
	void SetName(const std::string& name);
	/// @brief ���O�̎擾
	/// @return ���O
	const std::string& GetName();
	/// @brief �^�O�̎擾
	/// @return �^�O
	unsigned GetTag();
	/// @brief �^�O�̐ݒ�
	/// @param tag �ݒ肷��^�O
	void SetTag(unsigned tag);
	/// @brief Transform�̎擾
	/// @return Transform
	Transform* GetTransform();

	virtual bool Init()override;
	virtual void Update()override;
private:
	Name m_Name;						// �I�u�W�F�N�g��
	unsigned m_Tag;						// �^�O
	std::deque<std::unique_ptr<Component>> m_Components;	// �ǉ����ꂽ�R���|�[�l���g
};

#endif // !_____GameObject_HXX_____