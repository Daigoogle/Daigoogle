#include "Player.h"
#include "InputDeviceManager.h"
#include "Sprite.h"
#include "CubeCollisionToDirectManager.h"
#include "BaseObject.h"

//using namespace DirectX;

CPlayer::CPlayer() :
	m_pos(0.0f, 0.0f, 0.0f),
	m_pCamera(nullptr),
	m_Tf(nullptr)
{
	

	//モデルの生成
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/MokotaMememe.pmx", 0.05f, Model::XFlip))	//倍率、反転は省略可
	{
		MessageBox(NULL, " Assets/Model ", "Error", MB_OK);
	}

	//頂点シェーダーの読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);	//モデルへ読み込んだ頂点シェーダーを設定

	//影のテクスチャを設定	
	m_pShadow = new Texture;
	if (FAILED(m_pShadow->Create("Assets/Texture/takodane.png")))
	{
		MessageBox(NULL, " Assets/Texture PlayerShadow", "Error", MB_OK);
	}
	//マーカーのテクスチャを設定	
	m_pMarker = new Texture;
	if (FAILED(m_pMarker->Create("Assets/Texture/Marker.png")))
	{
		MessageBox(NULL, " Assets/Texture PlayerMarker", "Error", MB_OK);
	}

	m_pEffect = new Effect();
	m_pMoveEmitter = new MoveEmitter();
	m_pEffect->AddEmitter(m_pMoveEmitter);
	
	m_Acseraration = 0.0f;
}

CPlayer::~CPlayer()
{
	if (m_pModel)
	{
		delete m_pModel;
	}

	if (m_pVS)
	{
		delete m_pVS;
	}

	if (m_pShadow)
	{
		delete m_pShadow;
	}

	if (m_pMarker)
	{
		delete m_pMarker;
	}

	if (m_pMoveEmitter)
	{
		delete m_pMoveEmitter;
	}

	if (m_pEffect)
	{
		delete m_pEffect;
	}
}

void CPlayer::Init()
{
	m_Tf = GetBaseObject().GetComponent<Transform>();
	m_Tf->SetLocalPosition({ m_pos.x ,m_pos.y,m_pos.z });
	m_Tf->SetLocalScale({ 0.1f, 0.0f, 0.1f });
}

void CPlayer::UnInit()
{

}

void CPlayer::Update()
{
	m_Acseraration -= 0.003f;//重力
	bool isMove = false;
	const float Speed = 0.1f;
	const float pai = 3.141592f;

	DirectX::XMFLOAT3 camPos = m_pCamera->GetPos();
	DirectX::XMFLOAT3 camLook = m_pCamera->GetLook();
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);

	DirectX::XMVECTOR vFront;	//カメラの正面方向のベクトル
	vFront = DirectX::XMVectorSubtract(vCamLook , vCamPos);
	vFront = DirectX::XMVector3Normalize(vFront);//正規化(単位ベクトルの取得)

	DirectX::XMMATRIX matRotSide =DirectX::XMMatrixRotationY(pai/2);//ベクトルを90度回転
	DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront,matRotSide);
	DirectX::XMVECTOR vMove = DirectX::XMVectorZero();


	if (InputDevice::IsPress(KeyCodes::W)) 
	{ 
		isMove = true; 
		vMove = DirectX::XMVectorAdd(vMove, vFront); 
	}
	if (InputDevice::IsPress(KeyCodes::S))
	{ 
		isMove = true; 
		vMove = DirectX::XMVectorSubtract(vMove, vFront); 
	}
	if (InputDevice::IsPress(KeyCodes::D))
	{ 
		isMove = true; 
		vMove = DirectX::XMVectorAdd(vMove,vSide); 
	}
	if (InputDevice::IsPress(KeyCodes::A))
	{ 
		isMove = true; 
		vMove = DirectX::XMVectorSubtract(vMove,vSide); 
	}
	if (Singleton<CubeCollisionToDirectManager>::GetInstance().PlayerTachGround())
		if (InputDevice::IsTrigger(KeyCodes::Space))
			m_Acseraration += 0.1f;
		else
			m_Acseraration = 0.0f;

	//if (InputDevice::IsPress('Q')) { m_pos.y += Speed; }
	//if (InputDevice::IsPress('E')) { m_pos.y -= Speed; }

	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);
	vMove = DirectX::XMVectorScale(vMove,Speed);

	DirectX::XMFLOAT3 move;	//計算した移動ベクトルの格納先
	DirectX::XMStoreFloat3(&move,vMove);
	m_pos.x += move.x; m_pos.y += move.y + m_Acseraration; m_pos.z += move.z;	//座標の更新

	m_pEffect->Update();
	m_pEffect->SetPos(m_pos);
	if (!m_pEffect->IsPlay() && isMove)
	{
		m_pEffect->Play();
	}
	m_Tf->SetWorldPosition({ m_pos.x ,m_pos.y,m_pos .z});
}

void CPlayer::Draw()
{
	//カメラがなければ処理を行わない
	if(!m_pCamera)
	{
		return;
	}

	//行列の計算
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)));
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjMatrix();

	

	////モデル表示
	//m_pVS->WriteBuffer(0, mat);
	//if (m_pModel)
	//{
	//	m_pModel->Draw();
	//}

	//DirectX::XMMATRIX SmatT = DirectX::XMMatrixTranslation(m_pos.x, 0.0001f, m_pos.z);
	//DirectX::XMMATRIX SmatS = DirectX::XMMatrixRotationX(1.57079f);
	//DirectX::XMMATRIX matShadow = SmatS * SmatT;
	//DirectX::XMFLOAT4X4 world;
	//DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(matShadow));
	//Sprite::SetWorld(world);
	//Sprite::SetView(m_pCamera->GetViewMatrix());
	//Sprite::SetProjection(m_pCamera->GetProjMatrix());
	//Sprite::SetSize(DirectX::XMFLOAT2(0.5f, 0.5f));
	//Sprite::SetTexture(m_pShadow);
	//Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//Sprite::Draw();


	DirectX::XMFLOAT4X4 inv; //逆行列の格納先
	inv = m_pCamera->GetViewMatrix();

	//カメラ行列はGPUに渡す際に転置されているので元に戻す
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);

	// 移動成分は逆行列で打ち消す必要がないので、0を設定して移動を無視する
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr,matInv);


	// 頭上UI
	//DirectX::XMMATRIX Mmat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 1.4f, m_pos.z);
	//DirectX::XMMATRIX worldmat = matInv * Mmat;
	//DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(worldmat));
	//Sprite::SetWorld(mat[0]);
	//Sprite::SetTexture(m_pMarker);
	//Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//Sprite::Draw();

	//土煙
	DirectX::XMStoreFloat4x4(&inv,matInv);
	m_pEffect->SetBillboardMatrix(inv);
	m_pEffect->Draw(m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	
}

Transform* CPlayer::GetTransform()
{
	if (m_Tf == nullptr)
		m_Tf = GetBaseObject().GetComponent<Transform>();
	return m_Tf;
}