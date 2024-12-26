#include "CameraDebug.h"
#include "InputDeviceManager.h"
#include "GameObject.hxx"
#include "Transform.hxx"
#include "Time.hxx"

CameraDebug::CameraDebug()
{
}

CameraDebug::~CameraDebug()
{
}

bool CameraDebug::Init()
{
	m_Transform = GetGameObject().GetTransform();

	//m_look = Vec::ToXMFLOAT3(tf::RotationToVector(m_Transform->GetWorldRotation()) + m_Transform->GetWorldPosition());

	return true;
}

void CameraDebug::Update()
{
	float Speed = DeltaSeconds();
	Speed *= 3.0f;
	
	fVec3 LookRot = m_Transform->GetWorldRotation();

	//’Ž‹“_‚ð“®‚©‚·
	if (InputDevice::IsPress(KeyCodes::Up))		{ 
		LookRot.x += Speed*20; 
		if (LookRot.x >= 90.0f) LookRot.x = 89.999f;
	}
	if (InputDevice::IsPress(KeyCodes::Down))	{ 
		LookRot.x -= Speed*20; 
		if (LookRot.x <= -90.0f) LookRot.x = -89.999f;
	}
	if (InputDevice::IsPress(KeyCodes::Right))	{ LookRot.y += Speed*20; }
	if (InputDevice::IsPress(KeyCodes::Left))	{ LookRot.y -= Speed*20; }

	m_Transform->SetWorldRotation(LookRot);
	fVec3 LookVec = tf::RotationToVector(LookRot);

	fVec3 m_Move;

	if (InputDevice::IsPress(KeyCodes::W)) { m_Move	= m_Move + LookVec * Speed; }
	if (InputDevice::IsPress(KeyCodes::S)) { m_Move	= m_Move - LookVec * Speed; }
	if (InputDevice::IsPress(KeyCodes::A)) { 
		m_Move.x -= LookVec.z * Speed;
		m_Move.z += LookVec.x * Speed;
	}
	if (InputDevice::IsPress(KeyCodes::D)) { 
		m_Move.x += LookVec.z * Speed;
		m_Move.z -= LookVec.x * Speed;
	}

	if (InputDevice::IsPress(KeyCodes::Q)) { 
		m_Move.y += Speed;
	}
	if (InputDevice::IsPress(KeyCodes::E)) { 
		m_Move.y -= Speed;
	}

	//fVec3 m_pos;
	//m_pos.x = (cosf(m_radY) * sinf(m_radXZ) * m_radius )+ m_look.x;
	//m_pos.y = (sinf(m_radY) * m_radius )+ 1.0f;
	//m_pos.z = (cosf(m_radY) * cosf(m_radXZ) * m_radius )+ m_look.z;
	m_Transform->SetWorldPosition(m_Move + m_Transform->GetWorldPosition());

	m_look = Vec::ToXMFLOAT3(LookVec * 10 + m_Transform->GetWorldPosition());

	//this->GetGameObject().GetTransform()->SetLocalPosition({m_pos.x,m_pos.y,m_pos.z});
}																			
