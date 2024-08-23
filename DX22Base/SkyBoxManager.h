//	�t�@�C�����FCubeManager.h
//	�T�v		 �F�����̂̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/09	03:07	�쐬	
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SKY_BOX_MANAGER_H_____
#define _____SKY_BOX_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include <queue>
#include "CameraBase.h"
#include "MeshBuffer.h"
#include "SkyBoxComponent.h"
#include "SingletonsMng.hxx"

/// @brief �����̂̊Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
class SkyBoxManager final :public Singleton<SkyBoxManager>
{
	friend class Singleton<SkyBoxManager>;
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
	void AddQueue(SkyBoxComponent*);

private:
	SkyBoxManager();
	~SkyBoxManager();

	std::unique_ptr<MeshBuffer> m_MeshBuffer;
	std::queue<SkyBoxComponent*> m_queue;
};

#endif // !_____SKY_BOX_MANAGER_H_____