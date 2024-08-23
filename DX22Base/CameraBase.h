#ifndef ___CAMERA_H___
#define ___CAMERA_H___

#include <DirectXMath.h>
#include "Component.h"

class CameraBase:public Component
{
public:
	CameraBase();
	virtual ~CameraBase();

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjMatrix();

	//
	DirectX::XMFLOAT3 GetPos()
	{
		return m_pos;
	}
	//
	DirectX::XMFLOAT3 GetLook()
	{
		return m_look;
	}

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	//�r���[�s��ɕK�v�ȕϐ�
	float m_fovy, m_aspect,m_near,m_far;	//�v���W�F�N�V�����s��̐ݒ�ɕK�v�ȕϐ�

};

#endif