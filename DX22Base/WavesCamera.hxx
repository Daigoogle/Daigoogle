//	�t�@�C����	�FWavesCamera.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/12/13 22:21:44
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____WavesCamera_HXX_____
#define _____WavesCamera_HXX_____

// =-=-= �C���N���[�h�� =-=-=
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