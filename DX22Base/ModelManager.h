//	�t�@�C�����FModelManager.h
//	�T�v		 �F���f���̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/20	00:07	�쐬	
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____MODEL_MANAGER_H_____
#define _____MODEL_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include <queue>
#include "ModelComponent.h"
#include "SingletonsMng.hxx"

/// @brief ���f���̊Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
class ModelManager :public Singleton<ModelManager>
{
	friend Singleton<ModelManager>;
public:
	bool Init();
	void Update();
	void Draw();
	void UnInit();

	void AddQueue(ModelComponent* comp);

private:
	ModelManager();
	~ModelManager();
	struct tPositionCBuffer
	{
		DirectX::XMFLOAT4X4 world;		// ���[���h�s��
		DirectX::XMFLOAT4X4 view;		// �r���[�s��
		DirectX::XMFLOAT4X4 projection;	// �ˉe�s��
	};									//// ���W�̒萔�o�b�t�@

	struct tLightCBuffer
	{
		DirectX::XMFLOAT4	sourcePos;	// �����̍��W
		float				alpha;		// ���l
	};									//// ���C�g�̒萔�o�b�t�@	

	std::vector<ModelComponent*>	m_modelQueue;// ���f�����i�[����z��
	//std::unique_ptr<VertexShader>					m_vertexShader;
	//std::unique_ptr<PixelShader>					m_pixelShader;
	tPositionCBuffer						m_posCBuf;// ���W�̒萔�o�b�t�@
	tLightCBuffer							m_ligCBuf;// ���C�e�B���O�o�b�t�@

	std::queue<ModelComponent*> m_queue;
};

#endif // !_____MODEL_MANAGER_H_____