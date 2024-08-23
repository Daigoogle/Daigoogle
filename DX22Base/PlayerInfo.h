#ifndef _____PLAYER_INFO_H_____
#define _____PLAYER_INFO_H_____

#include "Component.h"

/// @brief �v���C���[�X�e�[�^�X�̕ۑ�������
/// @brief ����͕ʃN���X
class PlayerInfo :
    public Component
{
public:
	enum class PlayerMove
	{
		Move_Stand,
		Move_Walk,
		Move_Jump,
		Move_Max
	};

	PlayerInfo();
	~PlayerInfo();

	void Init()override;
	void Update()override;
	void UnInit()override;

	PlayerMove SetMove(PlayerMove);
	PlayerMove GetMove();
	PlayerMove SetOldMove(PlayerMove);
	PlayerMove GetOldMove();

private:
	PlayerMove m_Move;
	PlayerMove m_OldMove;
};

#endif // !_____PLAYER_INFO_H_____