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
	DirectX::XMFLOAT3 m_look, m_up;	//ビュー行列に必要な変数
	float m_fovy, m_aspect,m_near,m_far;	//プロジェクション行列の設定に必要な変数
	Transform* m_Transform;
};

#endif