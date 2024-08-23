#include "SoundEffectComponent.h"
#include "BaseObject.h"

SoundEffectComponent::SoundEffectComponent()
	: m_pTransform(nullptr)
	, m_SE_Start(AudioManager::SE_KIND::SE_MAX)
{
	
}

SoundEffectComponent::~SoundEffectComponent()
{

}

void SoundEffectComponent::Init()
{
	m_pTransform = GetBaseObject().GetComponent<Transform>();
}

void SoundEffectComponent::Update()
{
	if (m_SE_Start != AudioManager::SE_KIND::SE_MAX)
		AudioManager::GetInstance().AddSoundEffect(this);
}

void SoundEffectComponent::UnInit()
{

}

void SoundEffectComponent::PlaySE(AudioManager::SE_KIND se)
{
	m_SE_Start = se;
}

Transform* SoundEffectComponent::GetTransform()
{
	return m_pTransform;
}

AudioManager::SE_KIND SoundEffectComponent::GetSEKind()
{
	return m_SE_Start;
}
