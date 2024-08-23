#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
	: m_Move(PlayerMove::Move_Stand)
	, m_OldMove(PlayerMove::Move_Stand)
{

}

PlayerInfo::~PlayerInfo()
{

}

void PlayerInfo::Init()
{

}

void PlayerInfo::Update()
{

}

void PlayerInfo::UnInit()
{

}

PlayerInfo::PlayerMove PlayerInfo::SetMove(PlayerInfo::PlayerMove move)
{
	m_Move = move;
	return m_Move;
}

PlayerInfo::PlayerMove PlayerInfo::GetMove()
{
	return m_Move;
}

PlayerInfo::PlayerMove PlayerInfo::SetOldMove(PlayerInfo::PlayerMove oldMove)
{
	m_OldMove = oldMove;
	return m_OldMove;
}

PlayerInfo::PlayerMove PlayerInfo::GetOldMove()
{
	return m_OldMove;
}