#include "SceneBase.hxx"

#include "GameObject.hxx"
#include "GameObjectMng.hxx"

SceneBase::~SceneBase()
{
	GameObjectMng::GetInstance().DeleteSceneObjects(this);
}

GameObject SceneBase::MakeObject()
{
	return GameObjectMng::GetInstance().MakeObject(this);
}