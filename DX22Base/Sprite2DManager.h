//	�t�@�C�����FSprite2DManager.h
//	�T�v		 �F2D���ʃI�u�W�F�N�g�̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/18	00:52	�R�����g�ǉ�
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SPRITE_2D_MANAGER_H_____
#define _____SPRITE_2D_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "Sprite2DComponent.h"
#include "MeshBuffer.h"
#include <memory>
#include <queue>
#include "SingletonsMng.hxx"

/// @brief 2D���ʃI�u�W�F�N�g�̊Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
class Sprite2DManager final :public Singleton<Sprite2DManager>
{
	friend Singleton<Sprite2DManager>;
public:
	bool	Init(void);
	void	Draw(void);
	void	UnInit(void);
	void	AddQueue(Sprite2DComponent*);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	//	SetWindowSize
	//	�֐��T�v�F�E�B���h�E�T�C�Y��ݒ�
	//	�N���X�FCSprite2DManager
	//	���@���F�Ȃ�
	//	�Ԃ�l�F�Ȃ�
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	void	SetWindowSize();

private:
	Sprite2DManager();	//�R���X�g���N�^
	~Sprite2DManager();	//�f�X�g���N�^

	std::unique_ptr<MeshBuffer>		m_meshBuffer;
	std::queue<Sprite2DComponent*>	m_queue;
	fVec2 m_windowSize;
	static const float				NEAR_CLIP;
	static const float				FAR_CLIP;
};

#endif // !_____SPRITE_2D_MANAGER_H_____