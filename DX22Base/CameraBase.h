#ifndef ___CAMERA_H___
#define ___CAMERA_H___

#include <type_traits>
#include <DirectXMath.h>
#include "Transform.hxx"
#include "Component.hxx"

class CameraBase:public Component
{
public:
	CameraBase();
	virtual ~CameraBase();

	bool Init()override;

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjMatrix();

	//
	DirectX::XMFLOAT3 GetPos()
	{
		fVec3 pos = m_Transform->GetWorldPosition();
		return {pos.x,pos.y,pos.z};
	}
	//
	DirectX::XMFLOAT3 GetLook()
	{
		return m_look;
	}

	void SetMainCamera();

protected:
	DirectX::XMFLOAT3 m_look, m_up;	//�r���[�s��ɕK�v�ȕϐ�
	float m_fovy, m_aspect,m_near,m_far;	//�v���W�F�N�V�����s��̐ݒ�ɕK�v�ȕϐ�
	Transform* m_Transform;
};

#endif