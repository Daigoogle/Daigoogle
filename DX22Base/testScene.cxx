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
#include "Model.hxx"
#include "WaveCubeCmp.hxx"
#include "ParticleCmp.hxx"

testScene::testScene()
{

}

testScene::~testScene()
{

}

bool testScene::Init()
{
	GameObject obj;// = MakeObject();
	//Plane* cube = obj.AddComponent<Plane>();
	//obj.AddComponent<AnyUpdateComp>()->SetFunc([obj]()
	//{
	//	ShowUsingMemorySize();
	//});
	//cube->SetTexture("Assets/Texture/Init_FROM.png");
	//obj.GetTransform()->SetWorldScale({ 0.3f, 0.3f, 0.3f });
	//obj.GetTransform()->SetWorldPosition({0.5f,0.5f, 0.0f});
	//cube->SetLayer((LAYER_TYPE)2);

	GameObject Camra = MakeObject();
	Transform* CTF = Camra.GetTransform();
	CTF->SetWorldPosition({0.0f,0.0f,0.0f});
	CTF->SetWorldRotation({0.0f,30.0f,90.0f});

	Camra.AddComponent<WavesCamera>()->SetMainCamera();
	//Camra.AddComponent<CameraDebug>()->SetMainCamera();

	//obj.GetTransform()->LookPoint(Camra.GetTransform());

	for (int y = 0; y < 66; y++)
	{
		for (int x = 0; x < 66; x++)
		{
			obj = MakeObject();
			Cube* cube = obj.AddComponent<Cube>();
			cube->SetTexture("Assets/Texture/Alpha.png");
			Transform* tf = obj.GetTransform();
			tf->SetWorldScale({ 0.1f, 0.1f, 0.1f });
			tf->SetWorldPosition({ (x - 30) * 0.17f, 0.0f, (y - 30) * 0.17f });
			obj.AddComponent<WaveCubeCmp>();
		}
	}

	obj = MakeObject();
	obj.AddComponent<ParticleCmp>();
	obj.AddComponent<Plane>()->SetTexture("Assets/Texture/title.png");
	Transform* tf = obj.GetTransform();
	tf->LookPoint(CTF);
	tf->SetWorldScale({6.0f,4.0f,5.0f});
	tf->SetWorldPosition({ 0.0f,0.5f,0.0f });

	return true;
}