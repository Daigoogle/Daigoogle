#include "SceneComponentTest.h"
#include "BaseObjectManager.h"
#include "BaseObject.h"

#include "ModelComponent.h"
#include "CameraManager.h"
#include "CameraDebug.h"
#include "CubeComponent.h"
#include "Sprite3DComponent.h"
#include "SoundEffectComponent.h"
#include "fade.h"

SceneComponentTest::SceneComponentTest() 
{

}

SceneComponentTest::~SceneComponentTest()
{

}

void SceneComponentTest::Init()  
{
	BaseObject CameraObj = ObjectManager::Make(this);
	CameraManager::GetInstance().SetCamera(CameraObj.AddComponent<CameraDebug>());

	BaseObject TestModel = ObjectManager::Make(this);
	m_Se = TestModel.AddComponent<SoundEffectComponent>();
	Transform* tf = TestModel.GetComponent<Transform>();
	ModelComponent* model = TestModel.AddComponent<ModelComponent>();
	//CubeComponent* cube = TestModel.AddComponent<CubeComponent>();
	//cube->LoadTexture("Assets/Texture/defalt.png");
	//cube->SetPixelShader("Assets/Shader/DefaltModel_PS.cso");
	//cube->SetVertexShader("Assets/Shader/DefaltModel_VS.cso");
	//Sprite3DComponent* sprite = TestModel.AddComponent<Sprite3DComponent>();
	//sprite->LoadTexture("Assets/Texture/alpha.png");
	model->RegisterModel(0, "Assets/Model/test/Anim_Player_eat_1.fbx",true);
	tf->SetLocalScale({0.1f,0.1f,0.1f});
	//model->SelectModel(0);
	//model->SetAlpha(1.0f);
	//model->LoadPixelShader("Assets/Shader/DefaltModel_PS.cso");
	//model->LoadVertexShader("Assets/Shader/DefaltModel_VS.cso");
	//model->SelectModelWithAnime(0, true, 1.0f);

	AudioManager::GetInstance().IsStereo(true);

	Fade::GetInstance().InStart();
}

void SceneComponentTest::Update()
{
	m_Se->PlaySE(AudioManager::SE_KIND::SE_ENTER);
}

void SceneComponentTest::UnInit()
{

}
