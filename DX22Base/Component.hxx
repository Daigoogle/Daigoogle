//	�t�@�C����	�FComponent.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/16 9:43:49
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Component_HXX_____
#define _____Component_HXX_____

#include "GameObject.hxx"
#include "SceneBase.hxx"

class Component
{
	friend class GameObject;
	friend class SceneBase;
public:
	Component():m_pBaseObject(nullptr){};
	virtual ~Component() {}

	virtual bool Init() = 0;
	virtual void Update() = 0;

	/// @brief GameObject���擾����
	/// @brief ���Ӂ�SceneComponent�̏ꍇ�G���[
	/// @return �����Q�[���I�u�W�F�N�g
	GameObject* GetGameObject();
private:
	Object* m_pBaseObject;
};

#endif // !_____Component_HXX_____