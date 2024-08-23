#include "PlayerForce.h"
#include "BaseObject.h"
#include "PutLog.h"
#include "InputDeviceManager.h"
#include "ModelComponent.h"
#include "SoundEffectComponent.h"

#include "CubeCollisionToDirectManager.h"

PlayerForce::PlayerForce()
	: m_PlayerInfo(nullptr)
	, m_ModelComp(nullptr)
	, m_Transform(nullptr)
{

}

PlayerForce::~PlayerForce()
{

}

void PlayerForce::Init()
{
	BaseObject base = GetBaseObject();
	m_Transform = base.GetComponent<Transform>();
	if (m_Transform == nullptr)
		Error("Not Component : Transform\n to PlayerForce");
	m_PlayerInfo = base.GetComponent<PlayerInfo>();
	if (m_PlayerInfo == nullptr)
		Error("Not Component : PlayerInfo\n to PlayerForce");
	m_ModelComp = base.GetComponent<ModelComponent>();
	if (m_ModelComp == nullptr)
		Error("Not Component : ModelComponent\n to PlayerForce");

	m_Transform->SetWorldScale({0.1f,0.1f,0.1f});

	m_ModelComp->RegisterModel(static_cast<int>(PlayerInfo::PlayerMove::Move_Walk),"Assets/Model/Player/Anim_Player_run_1.fbx", true);
	m_ModelComp->RegisterModel(static_cast<int>(PlayerInfo::PlayerMove::Move_Jump),"Assets/Model/Player/Anim_Player_jump_1.fbx", true);
	m_ModelComp->RegisterModel(static_cast<int>(PlayerInfo::PlayerMove::Move_Stand), "Assets/Model/Player/Anim_Player_pose_1.fbx", true);
}

void PlayerForce::Update()
{
	PlayerInfo::PlayerMove move = m_PlayerInfo->GetMove();

	if (InputDevice::IsTrigger(KeyCodes::Space) 
		&& CubeCollisionToDirectManager::GetInstance().PlayerTachGround())
	{	// ジャンプモーション
		move = PlayerInfo::PlayerMove::Move_Jump;
		m_ModelComp->SelectModelWithAnime(static_cast<int>(move),false,1.0f);
		GetBaseObject().GetComponent<SoundEffectComponent>()->PlaySE(AudioManager::SE_KIND::SE_JUMP);
	}
	else if (CubeCollisionToDirectManager::GetInstance().PlayerTachGround()
		&&(InputDevice::IsPress(KeyCodes::W)
		|| InputDevice::IsPress(KeyCodes::A)
		|| InputDevice::IsPress(KeyCodes::S)
		|| InputDevice::IsPress(KeyCodes::D)))
	{	// 移動モーション
		if (move != PlayerInfo::PlayerMove::Move_Walk)
		{
			move = PlayerInfo::PlayerMove::Move_Walk;
			m_ModelComp->SelectModelWithAnime(static_cast<int>(move), true, 0.8f);
		}
	}
	else if(CubeCollisionToDirectManager::GetInstance().PlayerTachGround())
	{	// 待機モーション
		if (move != PlayerInfo::PlayerMove::Move_Stand)
		{
			move = PlayerInfo::PlayerMove::Move_Stand;
			m_ModelComp->SelectModelWithAnime(static_cast<int>(move), true, 0.7f);
		}
	}

	m_PlayerInfo->SetMove(move);
}

void PlayerForce::UnInit()
{

}
