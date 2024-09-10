#include "testScene.hxx"
#include "GameObject.hxx"
#include "Cube.hxx"
#include "CameraDebug.h"

#include "CameraManager.h"

testScene::testScene()
{

}

testScene::~testScene()
{

}

bool testScene::Init()
{
	GameObject obj = MakeObject();
	Cube* cube = obj.AddComponent<Cube>();
	cube->SetTexture("Assets/Texture/Init_FROM.png");

	GameObject Camra = MakeObject();
	CameraBase* cmr = Camra.AddComponent<CameraDebug>();
	CameraManager::GetInstance().SetMainCamera(cmr);

	return true;
}