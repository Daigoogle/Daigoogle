#include "CameraBase.h"

CameraBase::CameraBase():
	m_pos(0.0f,0.0f,-3.0f),
	m_look(0.0f,0.0f,0.0f),
	m_up(0.0f,1.0f,0.0f),
	m_fovy(1.0472f),
	m_aspect(16.0f/9.0f),
	m_near(0.3f),
	m_far(1000.0f)
{


}

CameraBase::~CameraBase()
{
}

DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	//
	//�r���[�s��̌v�Z
	view =
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),//�J�����̈ʒu
			DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),//�J�����̒��ڂ��Ă�ʒu
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f) //�J�����̏����
		);
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	//
	//�v���W�F�N�V�����s��̌v�Z
	proj = 
		DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);
	proj = DirectX::XMMatrixTranspose(proj);									   //������͈�
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}
