#ifndef __CAMERA_DEBUG_H___
#define __CAMERA_DEBUG_H___

#include "CameraBase.h"
#include "Component.h"

class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();

	void Init()override;
	void Update()override;
	void UnInit()override;

private:
	float m_radXZ;
	float m_radY;
	float m_radius;


};

#endif