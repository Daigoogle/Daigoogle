//	ファイル名	：WavesCamera.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/12/13 22:21:44
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____WavesCamera_HXX_____
#define _____WavesCamera_HXX_____

// =-=-= インクルード部 =-=-=
#include "CameraBase.h"

class WavesCamera :public CameraBase
{
public:
	WavesCamera();
	~WavesCamera();

protected:
	bool Init()override;
	void Update()override;

private:

};

#endif // !_____WavesCamera_HXX_____