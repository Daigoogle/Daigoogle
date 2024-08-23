#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneTitle.h"

#include "InputDeviceManager.h"
#include "DirectX11SetUp.h"
#include "CubeManager.h"
#include "Sprite3DManager.h"
#include "Sprite2DManager.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include "fade.h"
#include "CameraManager.h"

#include "BaseObject.h"
#include "BaseObjectManager.h"

#include "Geometory.h"
#include "CameraDebug.h"
#include "CameraPlayer.h"
#include "ModelComponent.h"
#include "PlayerInfo.h"
#include "PlayerForce.h"
#include "SoundEffectComponent.h"
#include "SkyBoxComponent.h"
#include "TextureRegister.h"

float af = 1.41421356f;

void SceneGame::Init()
{
	//m_pModel = new Model;
	//if (!m_pModel->Load("Assets/Model/MokotaMememe.pmx",0.05f, Model::XFlip))	//倍率、反転は省略可
	//{
	//	MessageBox(NULL, " Assets/Model ", "Error", MB_OK);
	//}


	////頂点シェーダーの読み込み
	//m_pVS = new VertexShader();
	//if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))
	//{
	//	MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	//}
	//m_pModel->SetVertexShader(m_pVS);	//モデルへ読み込んだ頂点シェーダーを設定

	//m_pCamera = new CameraDebug();
	g_bNext = 0;
	m_EndFlg = true;

	BaseObject cube1 = ObjectManager::Make(this);
	BaseObject cube2 = ObjectManager::Make(this);
	BaseObject player = ObjectManager::Make(this);
	BaseObject ground = ObjectManager::Make(this);
	BaseObject score = ObjectManager::Make(this);

	//g_pCubeS = new CubeComponent[2];
	g_pCubeS = new CubeComponent*[2];
	g_pCubeS[0] = cube1.AddComponent<CubeComponent>();
	g_pCubeS[1] = cube2.AddComponent<CubeComponent>();


	g_pCCollS = new CubeCollisionToDirectComponent[2];
	m_BlockPos = { 0.0f,0.0f,0.0f };
	m_pPlayer = player.AddComponent<CPlayer>();
	player.AddComponent<ModelComponent>();
	player.AddComponent<PlayerInfo>();
	player.AddComponent<PlayerForce>();
	player.AddComponent<SoundEffectComponent>();
	player.AddComponent<SkyBoxComponent>()->LoadTexture("Assets/Texture/cube_map.png");
	player.SetActive(false);
	m_mainCamera = CAM_PLAYER;
	m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer);
	m_pCamera[CAM_DBG] = new CameraDebug();
	m_pPlayer->SetCamera(m_pCamera[CAM_PLAYER]);

	CameraManager::GetInstance().SetCamera(m_pCamera[m_mainCamera]);

	g_PlayerColl = new CubeCollisionToDirectComponent;
	g_PlayerColl->SetTransform(player.GetComponent<Transform>());

	score.GetComponent<Transform>()->SetLocalPosition({ 0.45f,-0.38f,0.0f });
	g_NumBer = score.AddComponent<NumSprite2D>();

	g_WG = ground.AddComponent<Sprite3DComponent>();
	//ground.SetActive(false);
#if 0
	g_WG->LoadTexture(0,"Assets/Texture/shima.jpg");
#else
	g_WG->LoadTexture(0,"Assets/Texture/Orange_13_Base_Color.png");
	//g_WG->LoadTexture(0,"Assets/Texture/ground.png");
#endif
	g_WG->SetPixelShader("Assets/Shader/HexTiling.cso");

	g_WG->GetPixelShader()->AddTextureBuff();
	g_WG->LoadTexture(1, "Assets/Texture/hexTiling.png");

	g_WG->RegisterDataPixelShader(0, sizeof(float));
	g_WG->WriteDataPixelShader(0, &af, sizeof(float));

	g_WG->SetColor({1.3f,1.0f, 1.0f ,1.0f});
	Transform* wgtf = ground.GetComponent<Transform>();
	wgtf->SetLocalPosition({0.0f,0.0f,-1.0f});
	wgtf->SetLocalRotation({20.0f,180.0f,0.0f});
	wgtf->SetLocalScale({14.0f,14.0f, 14.0f});

	g_pCubeS[g_bNext]->Init();
	g_pCubeS[g_bNext]->GetTransform()->SetLocalPosition({ 0.0f,-0.25f,0.0f });
	g_pCubeS[g_bNext]->GetTransform()->SetLocalScale({ 2.0f,0.5f,2.0f });
	g_pCubeS[g_bNext]->SetColor({1.0f,0.2f,0.2f,0.0f});

	g_pCCollS[g_bNext].SetTransform(g_pCubeS[g_bNext]->GetTransform());
	g_pCCollS[g_bNext].SetTag(CollisionTag::GROUND);
	g_pCCollS[g_bNext].Commit();

	int posss = rand();
	fVec3 AddPos = {
				((posss & 0xF000) >> 12) * 0.33f - 1.6f,
				((posss & 0xF00) >> 8) * 0.01f + 1.0f,
				(posss & 0xFF) * 0.002f - 3.0f };
	m_BlockPos = m_BlockPos + AddPos;

	g_pCubeS[g_bNext ^ 1]->Init();
	g_pCubeS[g_bNext ^ 1]->GetTransform()->SetLocalPosition(m_BlockPos);
	g_pCubeS[g_bNext ^ 1]->GetTransform()->SetLocalScale({ 1.0f,0.5f,1.0f });

	g_pCCollS[g_bNext ^ 1].SetTransform(g_pCubeS[g_bNext ^ 1]->GetTransform());
	g_pCCollS[g_bNext ^ 1].SetTag(CollisionTag::GROUND);
	g_pCCollS[g_bNext ^ 1].Commit();

	g_PlayerColl->SetTransform(m_pPlayer->GetTransform());
	g_PlayerColl->SetTag(CollisionTag::PLAYER);
	g_PlayerColl->Commit();
	//g_bNext ^= 1;
	ScoreManager::GetInstance().Init();
	AudioManager::GetInstance().PlayBGM(AudioManager::BGM_KIND::BGM_GAME);
	Fade::GetInstance().InStart();
}

void SceneGame::UnInit()
{
	/*for (int i = 0; i < MAX_CAM; i++)
	{
		delete m_pCamera[i];
		m_pCamera[i] = nullptr;
	}*/

	//delete m_pPlayer;

	/*if (m_pModel)
	{
		dlete m_pModel;
		m_pModel = nullptr;
	}
	
	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}*/

	Singleton<CubeCollisionToDirectManager>::GetInstance().Crear();
}

void SceneGame::Update()
{
	static bool oldTuch = false;

	//回転のプログラム
	/*
	static float rad = 0.0f;
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(rad);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(rad);//radを使って回転
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(0);//radを使って回転
	DirectX::XMMATRIX mat = Rx * Ry * Rz;//行列を一つにまとめる計算

	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat; //行列の格納先
	DirectX::XMStoreFloat4x4(&fMat , mat);
	Geometory::SetWorld(fMat);//ボックスに変換行列を設定
	rad += tick; //回転の更新
	*/

	af += 0.0001f;
	g_WG->WriteDataPixelShader(0, &af, sizeof(float));

	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(0.0f,-0.05f,0.0f);
	DirectX::XMMATRIX S =
		DirectX::XMMatrixScaling( 2.0f, 0.1f, 2.0f);
	DirectX::XMMATRIX mat = S * T;

	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat; //行列の格納先
	DirectX::XMStoreFloat4x4(&fMat, mat);
	Geometory::SetWorld(fMat);//ボックスに変換行列を設定

	//if (m_mainCamera == CAM_PLAYER) { m_pPlayer->Update(); }

	m_pCamera[m_mainCamera]->Update();

	if (/*IsKeyPress('C')*/InputDevice::IsPress(KeyCodes::C)) {
		if (InputDevice::IsPress(KeyCodes::Num_1)) { m_mainCamera = CAM_DBG; }
		if (InputDevice::IsPress(KeyCodes::Num_2)) { m_mainCamera = CAM_PLAYER; }
		m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);//選択中のカメラをプレイヤーに設定
	}

	//if (CubeCollisionToDirectManager::GetInstance().PlayerTachGround())
	//	int i = 0;

	Singleton<CubeCollisionToDirectManager>::GetInstance().Update();
	if(InputDevice::IsTrigger(KeyCodes::Space))
	{
		if (Singleton<CubeCollisionToDirectManager>::GetInstance().PlayerTachGround())
		{
			int posss = rand();
			fVec3 AddPos = {
				((posss & 0xF000) >> 12) * 0.33f - 1.6f,
				((posss & 0xF00) >> 8) * 0.01f + 1.0f,
				(posss & 0xFF) * 0.002f - 3.0f };
			m_BlockPos = m_BlockPos + AddPos;
			g_pCubeS[g_bNext]->GetTransform()->SetLocalPosition(m_BlockPos);
			g_pCubeS[g_bNext]->GetTransform()->SetLocalScale({ 1.0f,0.5f,1.0f });
			g_pCubeS[g_bNext]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			ScoreManager::GetInstance().increase();
			
			g_bNext ^= 1;
		}
	}

	g_NumBer->SetNum(ScoreManager::GetInstance().GetScore());

	if (m_pPlayer->GetPos().y < -0.5f) //場外なら
	{
		if(m_EndFlg)
			Singleton<Fade>::GetInstance().OutStart();
		m_EndFlg = false;
		if(Singleton<Fade>::GetInstance().GetEnd())
			Singleton<SceneManager>::GetInstance().ChangeScene<SceneResult>();
	}
}

void SceneGame::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];		//ワールド、ビュープロジェクションの格納先

	DirectX11SetUp& Dx11 = Singleton<DirectX11SetUp>::GetInstance();

	RenderTarget* pRT = Dx11.GetDefaultRTV();//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDS = Dx11.GetDefaultDSV();//DeapthStencilViewの取得
	Dx11.SetRenderTargets(1, &pRT, pDS);
	


	//ワールド行列の計算
	DirectX::XMMATRIX Tm = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	DirectX::XMMATRIX Sm = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	DirectX::XMMATRIX world = Sm * Tm;
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0],world);

	////ビュー行列の計算
	//DirectX::XMMATRIX view =
	//DirectX::XMMatrixLookAtLH(
	//	DirectX::XMVectorSet(0.5f, 1.0f, -1.5f, 0.0f),//カメラの位置
	//	DirectX::XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),//カメラの注目してる位置
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) //カメラの上方向
	//);
	//view = DirectX::XMMatrixTranspose(view);
	//DirectX::XMStoreFloat4x4(&mat[1], view);
	//

	////プロジェクション行列の計算
	//DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(1.0472f, 16.0f/9.0f ,1.0f,10.0f);
	//proj = DirectX::XMMatrixTranspose(proj);									   //見える範囲
	//DirectX::XMStoreFloat4x4(&mat[2], proj);

	mat[1] = m_pCamera[m_mainCamera]->GetViewMatrix();
	mat[2] = m_pCamera[m_mainCamera]->GetProjMatrix();

	//行列をシェーダーに設定
	/*m_pVS->WriteBuffer(0, mat);



	if (m_pModel)
	{
		m_pModel->Draw();
	}
*/

	DirectX::XMMATRIX Tg = DirectX::XMMatrixTranslation(0.0f, -0.05f, 0.0f);
	DirectX::XMMATRIX Sg = DirectX::XMMatrixScaling(3.0f, 0.1f, 3.0f);
	world = Sg * Tg;
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	//SetRenderTargets(1, &pRT, GetDefaultDSV());// 深度バッファ

	//Geometory::DrawCylinder();

	m_pPlayer->Draw();

	//m_Item.Draw();

	

	
}