#include "CameraPlayer.h"
#include "InputDeviceManager.h"
#include "easing.h"
#include "GameObject.hxx"

CameraPlayer::CameraPlayer()
	: m_radXZ(-3.5f)
	, m_radY(0.1f)
	, m_dist(1.0f)
	, m_Frame(0)
{
}

CameraPlayer::~CameraPlayer()
{

}

void CameraPlayer::Update()
{
	m_look = Vec::ToXMFLOAT3(this->GetGameObject().GetTransform()->GetWorldPosition());//注視点をプレイヤーの位置とする
	m_look.y += 0.4f;	//位置調整

	const float Speed = 0.1f;

	if (m_Frame < 161)
	{
		float eas = Easing::InOutQuint(m_Frame / 160.0f);
		m_radXZ = -3.5f + eas * 3.5f;
		m_radY = eas * 0.3f + 0.1f;
		m_dist = eas * 4 + 1;

		m_Frame++;
	}
	else
	{
		if (InputDevice::IsPress(KeyCodes::Up)) { m_radY += Speed; }
		if (InputDevice::IsPress(KeyCodes::Down)) 
		{ 
			if(m_radY > 0.12f)
				m_radY -= Speed; 
		}
		if (InputDevice::IsPress(KeyCodes::Right)) { m_radXZ -= Speed; }
		if (InputDevice::IsPress(KeyCodes::Left)) { m_radXZ += Speed; }
	}

	fVec3 m_pos;
	//注視点に回り込む計算
	m_pos.x = (cosf(m_radY) * sinf(m_radXZ) * m_dist) + m_look.x;
	m_pos.y = (sinf(m_radY) * m_dist) + m_look.y;
	m_pos.z = (cosf(m_radY) * cosf(m_radXZ) * m_dist) + m_look.z;
	m_Transform->SetWorldPosition(m_pos);
}
