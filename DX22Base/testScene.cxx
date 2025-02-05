#include "testScene.hxx"
#include "GameObject.hxx"
// =-= マネージャー =-=
#include "CameraManager.h"
// =-= コンポーネント =-=
#include "Plane.hxx"
#include "Cube.hxx"
#include "CameraDebug.h"
#include "WavesCamera.hxx"
#include "AnyUpdateComp.hxx"
#include "WaveCubeCmp.hxx"

testScene::testScene()
{

}

testScene::~testScene()
{

}

bool testScene::Init()
{
	{
		GameObject& Camra = thisCreateObject<GameObject>();
		Transform* CTF = Camra.GetTransform();
		CTF->SetWorldPosition({ 0.0f,0.0f,0.0f });
		CTF->SetWorldRotation({ 0.0f,30.0f,90.0f });

		Camra.AddComponent<CameraDebug>()->SetMainCamera();
	}

	GameObject& obj = thisCreateObject<GameObject>();
	Plane* plane = obj.AddComponent<Plane>();
	plane->SetTexture("Assets/Texture/Init_FROM.png");

	//for (int y = 0; y < 12; y++)
	//{
	//	for (int x = 0; x < 12; x++)
	//	{
	//		GameObject& obj_ = thisCreateObject<GameObject>();
	//		Cube* cube = obj_.AddComponent<Cube>();
	//		cube->SetTexture("Assets/Texture/Alpha.png");
	//		Transform* tf = obj_.GetTransform();
	//		tf->SetWorldScale({ 0.1f, 0.1f, 0.1f });
	//		tf->SetWorldPosition({ (x - 6) * 0.17f, 0.0f, (y - 6) * 0.17f });
	//		obj_.AddComponent<WaveCubeCmp>();
	//	}
	//}

	return true;
}