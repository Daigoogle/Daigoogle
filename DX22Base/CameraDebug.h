#ifndef __CAMERA_DEBUG_H___
#define __CAMERA_DEBUG_H___

#include "CameraBase.h"

class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();

protected:
	void Update()override;

private:
	float m_radXZ;
	float m_radY;
	float m_radius;

};

#endif