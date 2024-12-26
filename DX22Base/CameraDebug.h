#ifndef __CAMERA_DEBUG_H___
#define __CAMERA_DEBUG_H___

#include "CameraBase.h"

class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();

protected:
	bool Init()override;
	void Update()override;

private:
};

#endif