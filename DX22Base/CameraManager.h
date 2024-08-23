//	�t�@�C�����FCameraManager.h
//	�T�v		 �F�J�������̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/17	21:40	�R�����g�ǉ�
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____CAMERA_MANAGER_H_____
#define _____CAMERA_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "CameraBase.h"
#include "SingletonsMng.hxx"

/// @brief �J�����̏����Ǘ�����
/// @brief ������������ �V���O���g���ł� ������������
class CameraManager final :public Singleton<CameraManager>
{
	friend class Singleton<CameraManager>;
public:
	void SetCamera(CameraBase*);
	CameraBase* GetMainCamera();

private:
	CameraManager();
	~CameraManager();
	CameraBase* m_pMainCamera;
};

#endif // !_____CAMERA_MANAGER_H_____