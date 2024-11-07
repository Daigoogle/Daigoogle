#include "testScene.hxx"
#include "GameObject.hxx"
// =-= マネージャー =-=
#include "CameraManager.h"
// =-= コンポーネント =-=
#include "Plane.hxx"
#include "Cube.hxx"
#include "CameraDebug.h"
#include "AnyUpdateComp.hxx"
#include "Model.hxx"

testScene::testScene()
{

}

testScene::~testScene()
{

}

bool testScene::Init()
{
	GameObject obj = MakeObject();
	Plane* cube = obj.AddComponent<Plane>();
	//obj.AddComponent<AnyUpdateComp>()->SetFunc([obj]()
	//{
	//	ShowUsingMemorySize();
	//});
	cube->SetTexture("Assets/Texture/Init_FROM.png");
	obj.GetTransform()->SetWorldScale({ 0.3f, 0.3f, 0.3f });
	obj.GetTransform()->SetWorldPosition({0.5f,0.5f, 0.0f});
	cube->SetLayer((LAYER_TYPE)2);

	GameObject Camra = MakeObject();
	Camra.AddComponent<CameraDebug>()->SetMainCamera();

	obj.GetTransform()->LookPoint(Camra.GetTransform());

	GameObject obj1[2];
	for(int y = 0; y < 1000;y++)
	{
		obj1[y%2] = MakeObject();
		Cube* cube = obj1[y % 2].AddComponent<Cube>();
		AnyUpdateComp* any = obj1[y % 2].AddComponent<AnyUpdateComp>();
		any->SetFunc([any]()
		{
			Transform* tf = any->GetGameObject().GetTransform();
			fVec3 R = tf->GetLocalRotation();
			tf->SetLocalRotation({ 0.0f,R.y + 0.0001f,0.0f });
		});
		cube->SetTexture("Assets/Texture/Kimchee_01_Base_Color.png");
		obj1[y%2].GetTransform()->SetWorldScale({ 0.1f, 0.1f, 0.1f });
		obj1[y%2].GetTransform()->SetWorldPosition({ cosf(y * 0.1f) * y * 0.02f, 0.0f, sinf(y * 0.1f) * y * 0.02f });
		if(y > 0)
			obj1[y % 2].GetTransform()->SetParent(obj1[y % 2 ^ 1].GetTransform());
	}

	//GameObject Mdl = MakeObject();
	//Model* mold = Mdl.AddComponent<Model>();
	//Mdl.GetTransform()->SetWorldScale({10.0f,10.0f ,10.0f });
	//mold->SetModel("Assets/Model/GM31/sky.obj");
	//mold->SetLayer((LAYER_TYPE)1);

	return true;
}