#include "CameraDebug.h"
#include "InputDeviceManager.h"
#include "GameObject.hxx"
#include "Transform.hxx"
#include "Time.hxx"

CameraDebug::CameraDebug():
	m_radXZ(0.0f),
	m_radY(0.0f),
	m_radius(1.0f)
{
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	const float Speed = DeltaSeconds();

	//注視点を動かす
	if (InputDevice::IsPress(KeyCodes::Up)) { m_look.z += Speed; }
	if (InputDevice::IsPress(KeyCodes::Down)) { m_look.z -= Speed; }
	if (InputDevice::IsPress(KeyCodes::Right)) { m_look.x += Speed; }
	if (InputDevice::IsPress(KeyCodes::Left)) { m_look.x -= Speed; }
	if (InputDevice::IsPress(KeyCodes::Shift)) { m_look.y += Speed; }
	if (InputDevice::IsPress(KeyCodes::Control)){ m_look.y -= Speed; }

	if (InputDevice::IsPress(KeyCodes::W)) { m_radY += Speed; }
	if (InputDevice::IsPress(KeyCodes::S)) { m_radY -= Speed; }
	if (InputDevice::IsPress(KeyCodes::A)) { m_radXZ += Speed; }
	if (InputDevice::IsPress(KeyCodes::D)) { m_radXZ -= Speed; }
	if (InputDevice::IsPress(KeyCodes::Q)) { m_radius += Speed; }
	if (InputDevice::IsPress(KeyCodes::E)) { m_radius -= Speed; }

	fVec3 m_pos;
	m_pos.x = (cosf(m_radY) * sinf(m_radXZ) * m_radius )+ m_look.x;
	m_pos.y = (sinf(m_radY) * m_radius )+ 1.0f;
	m_pos.z = (cosf(m_radY) * cosf(m_radXZ) * m_radius )+ m_look.z;
	m_Transform->SetWorldPosition(m_pos);

	m_look = { 0.0f,0.0f,0.0f };
	
	this->GetGameObject().GetTransform()->SetLocalPosition({m_pos.x,m_pos.y,m_pos.z});
}																			
