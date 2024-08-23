#ifndef _____PLAYER_FORCE_H_____
#define _____PLAYER_FORCE_H_____

#include "PlayerInfo.h"
#include "Component.h"

class ModelComponent;
class Transform;

/// @brief プレイヤーステータスの操作
/// @brief 数値格納部分は別。あくまで操作
class PlayerForce : public Component
{
public:
    PlayerForce();
    ~PlayerForce();

    void Init()override;
    void Update()override;
    void UnInit()override;

private:
    PlayerInfo* m_PlayerInfo;
    ModelComponent* m_ModelComp;
    Transform* m_Transform;
};

#endif // !_____PLAYER_FORCE_H_____