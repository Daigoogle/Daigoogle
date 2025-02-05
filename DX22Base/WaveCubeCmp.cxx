#include "WaveCubeCmp.hxx"

#include "Time.hxx"

WaveCubeCmp::WaveCubeCmp()
	: m_Time(0.0f)
	, m_Transform(nullptr)
{

}

WaveCubeCmp::~WaveCubeCmp()
{

}

bool WaveCubeCmp::Init()
{
	m_Transform = GetGameObject()->GetTransform();
	return true;
}

void WaveCubeCmp::Update()
{
	m_Time += DeltaSeconds()*6;
	float size = std::sinf( Vec::length(m_Transform->GetWorldPosition()) * 3.0f - m_Time) + 1.5f ;
	size *= 0.05f;
	m_Transform->SetWorldScale({ size, size, size });
	GetGameObject();
}