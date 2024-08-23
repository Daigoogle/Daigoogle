//	�t�@�C�����FSprite3DManager.h
//	�T�v		 �F3D�̕��ʃI�u�W�F�N�g�̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/17	21:40	�R�����g�ǉ�
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SPRITE_3D_MANAGER_H_____
#define _____SPRITE_3D_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "MeshBuffer.h"
#include "CameraBase.h"
#include <queue>
#include <memory>
#include "Sprite3DComponent.h"
#include "SingletonsMng.hxx"

/// @brief 3D��ԏ�̕��ʃI�u�W�F�N�g���Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
class Sprite3DManager :public Singleton<Sprite3DManager>
{
	friend Singleton<Sprite3DManager>;
private:
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};
public:
	bool Init();
	void Draw();
	void UnInit();
	void AddQueue(Sprite3DComponent*);
private:
	Sprite3DManager();
	~Sprite3DManager();
	std::unique_ptr<MeshBuffer> m_MeshBuffer;
	std::queue<Sprite3DComponent*> m_queue;

};

#endif // !_____SPRITE_3D_MANAGER_H_____