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

	//for(int y = 0; y < 300;y++)
	//{
	//	for (int x = 0; x < 30; x++)
	//	{
	//		GameObject obj = MakeObject();
	//		Cube* cube = obj.AddComponent<Cube>();
	//		cube->SetTexture("Assets/Texture/Kimchee_01_Base_Color.png");
	//		obj.GetTransform().SetWorldScale({ 0.1f, 0.1f, 0.1f });
	//		obj.GetTransform().SetLocalPosition({ (float)x, 0.0f, (float)y });
	//	}
	//}
	
	GameObject Camra = MakeObject();
	Camra.AddComponent<CameraDebug>()->SetMainCamera();
	
	return true;
}