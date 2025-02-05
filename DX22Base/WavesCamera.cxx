#include "WavesCamera.hxx"
#include "CameraDebug.h"
#include "GameObject.hxx"
#include "Transform.hxx"
#include "Time.hxx"

WavesCamera::WavesCamera()
{
}

WavesCamera::~WavesCamera()
{
}

bool WavesCamera::Init()
{
	m_Transform = GetGameObject()->GetTransform();
	m_Transform->SetWorldPosition({ 0.0f, 2.75f, 0.0f });
	m_Transform->SetWorldRotation({ -90.0f, 180.0f, 0.0f });
	//m_look = Vec::ToXMFLOAT3(tf::RotationToVector(m_Transform->GetWorldRotation()) + m_Transform->GetWorldPosition());

	return true;
}

void WavesCamera::Update()
{
	float Speed = DeltaSeconds();
	Speed *= 5.0f;

	fVec3 LookRot = m_Transform->GetWorldRotation();

	//’Ž‹“_‚ð“®‚©‚·
	//LookRot.y += Speed;
	m_Transform->SetWorldRotation(LookRot);
	fVec3 LookVec = tf::RotationToVector(LookRot);

	m_look = Vec::ToXMFLOAT3(LookVec * 10 + m_Transform->GetWorldPosition());
}
