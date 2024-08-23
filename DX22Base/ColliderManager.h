//	�t�@�C�����FColliderManager.h
//	�T�v		 �F�����蔻��̃I�u�W�F�N�g���܂Ƃ߂�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/01/20	19:20	�쐬	
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____COLLIDER_MANAGER_H_____
#define _____COLLIDER_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "Model.h"
#include "Vectors.hxx"
#include <vector>
#include "ColliderBase.h"
#include "ColliderJudgement.cuh"
#include "SingletonsMng.hxx"

/// @brief �����蔻����擾����
/// @brief ������������ �V���O���g���ł� ������������
class ColliderManager final :public Singleton<ColliderManager>
{
	friend class Singleton<ColliderManager>;
public:
	bool Init();
	void Update();
	void UnInit();
	
	void AddCollision(std::weak_ptr<ColliderBase*> add);

	std::vector<std::weak_ptr<ColliderBase*>> GetCollisions();

private:
	ColliderManager();
	~ColliderManager();

	std::unique_ptr<ColliderJudgement> m_ColliderJudgement;
	std::vector<std::weak_ptr<ColliderBase*>> m_Collisions;

};

#endif // !_____COLLIDER_MANAGER_H_____