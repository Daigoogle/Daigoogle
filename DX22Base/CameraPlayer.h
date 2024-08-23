#ifndef ____CAMERA_PLAYER_H____
#define ____CAMERA_PLAYER_H____

#include"Player.h"
#include "CameraBase.h"

class CameraPlayer : public CameraBase
{
public:
	CameraPlayer(CPlayer* pPlayer);
	~CameraPlayer();

	void Init()override;
	void Update()override;
	void UnInit()override;

private:
	CPlayer* m_pPlayer;
	int m_Frame;
	float m_radXZ;
	float m_radY;
	float m_dist;
};


#endif // !____CAMERA_PLAYER_H____

