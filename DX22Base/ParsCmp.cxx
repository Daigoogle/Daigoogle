#include "ParsCmp.hxx"
#include "CameraManager.h"

ParsCmp::ParsCmp()
{
	m_Direction = { 0, static_cast<float>(rand() % 360), 0};
}

ParsCmp::~ParsCmp()
{

}

bool ParsCmp::Init()
{
	m_Transform = GetGameObject().GetTransform();
	m_Transform->SetWorldScale({ 0.05f, 0.05f, 0.05f });
	m_Transform->SetWorldPosition({ 0, -1, 0 });
	m_Transform->SetWorldRotation({ -30, -30, -30 });
	m_Transform->LookPoint(CameraManager::GetInstance().GetMainCamera()->GetGameObject().GetTransform());
	return true;
}

void ParsCmp::Update()
{
	m_Direction.y += ((rand() % 1000) - 500) / 200.0f;
	m_Transform->SetWorldPosition(m_Transform->GetWorldPosition() + tf::RotationToVector(m_Direction)*0.01f);
}