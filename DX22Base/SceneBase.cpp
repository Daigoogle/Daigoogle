#include "SceneBase.h"

SceneBase::SceneBase()
	:m_bIsLoadScene(false)
{
	
}

SceneBase::~SceneBase()
{
	
}

void SceneBase::SetIsLoadScene(bool bIsLoad)
{
	m_bIsLoadScene = bIsLoad;
}

bool SceneBase::GetIsLoadScene()
{
	return m_bIsLoadScene;
}

