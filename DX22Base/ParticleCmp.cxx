#include "ParticleCmp.hxx"
#include "Time.hxx"
#include "SceneMng.hxx"
#include "Plane.hxx"
#include "ParsCmp.hxx"

ParticleCmp::ParticleCmp()
	: m_Particles()
	, m_Time(0.0f)
	, m_Scene(nullptr)
	, m_cnt(0)
{

}

ParticleCmp::~ParticleCmp()
{

}

bool ParticleCmp::Init()
{
	m_Scene = SceneMng::GetInstance().GetNowScene();
	return true;
}

void ParticleCmp::Update()
{
	m_Time += DeltaSeconds();
	if (m_Time < 0.1f)
		return;

	m_Time = 0.0f;

	if (m_Particles.size() < 100)
	{
		GameObject obj = m_Scene->MakeObject();
		m_Particles.push_back(obj.GetTransform());
		Plane* plane = obj.AddComponent<Plane>();
		plane->SetTexture("Assets/Texture/particle.png");
		obj.AddComponent<ParsCmp>();
		return;
	}

	if(m_cnt > 99)
		m_cnt = 0;
	m_Particles[m_cnt]->SetWorldPosition({ 0, -1, 0 });
	m_cnt++;
}