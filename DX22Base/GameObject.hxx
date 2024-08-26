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
#include "GameObjectInst.hxx"

class GameObject
{
public:
	GameObject();
	GameObject(GameObjectInst* pInstance);
	~GameObject();

	void SetInstance(GameObjectInst* pInstance);
	bool IsNull() const;

	/// @brief �R���|�[�l���g�̒ǉ�
	/// @tparam TypeComp �ǉ�����R���|�[�l���g�̌^
	/// @return �ǉ������R���|�[�l���g�̃|�C���^
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* AddComponent()
	{
		if (!m_pInstance)
			return nullptr;
		return m_pInstance->AddComponent<TypeComp>();
	}

	/// @brief �R���|�[�l���g�̎擾
	/// @tparam TypeComp �擾����R���|�[�l���g�̌^
	/// @return �擾�����R���|�[�l���g�̃|�C���^
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* GetComponent()
	{
		if (!m_pInstance)
			return nullptr;
		return m_pInstance->GetComponent<TypeComp>();
	}

	/// @brief �q�I�u�W�F�N�g��ǉ�
	/// @param pChild �ǉ�����q�I�u�W�F�N�g
	void AddChild(GameObject& pChild);
	/// @brief �q�I�u�W�F�N�g�𕪗�
	/// @param pChild ��������q�I�u�W�F�N�g
	void RemoveChild(GameObject& pChild);

	/// @brief �L�����ǂ���
	/// @return �L���Ȃ�true
	const bool IsActive();
	/// @brief �L�����ǂ�����ݒ�
	/// @param isActive �L���ɂ���Ȃ�true
	void SetActive(bool isActive);
	/// @brief ID�̎擾
	/// @return ID
	const unsigned __int64 GetID();
	/// @brief ���O�̐ݒ�
	/// @param name �ݒ肷�閼�O
	void SetName(const std::string& name);
	/// @brief ���O�̎擾
	/// @return ���O
	const std::string& GetName();
	/// @brief �e�I�u�W�F�N�g�̎擾
	/// @return �e�I�u�W�F�N�g
	GameObject GetParent();
	/// @brief �^�O�̎擾
	/// @return �^�O
	unsigned GetTag();
	/// @brief �^�O�̐ݒ�
	/// @param tag �ݒ肷��^�O
	void SetTag(unsigned tag);
	/// @brief �V�[���̎擾
	/// @return �V�[��
	SceneBase* GetScene();
private:
	GameObjectInst* m_pInstance;// ����
};

#endif // !_____GameObject_HXX_____