#ifndef ____CAMERA_PLAYER_H____
#define ____CAMERA_PLAYER_H____

#include "CameraBase.h"

class CameraPlayer : public CameraBase
{
public:
	CameraPlayer();
	~CameraPlayer();

protected:
	bool Init()override;
	void Update()override;

private:
	int m_Frame;
	float m_radXZ;
	float m_radY;
	float m_dist;
};


#endif // !____CAMERA_PLAYER_H____

