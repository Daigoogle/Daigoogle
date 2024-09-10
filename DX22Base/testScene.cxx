#include "testScene.hxx"
#include "GameObject.hxx"
#include "plane.hxx"

testScene::testScene()
{

}

testScene::~testScene()
{

}

bool testScene::Init()
{
	GameObject obj = MakeObject();
	obj.AddComponent<plane>();

	return true;
}