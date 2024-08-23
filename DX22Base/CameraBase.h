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
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	//ビュー行列に必要な変数
	float m_fovy, m_aspect,m_near,m_far;	//プロジェクション行列の設定に必要な変数

};

#endif