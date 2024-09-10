//	t@CผFCameraManager.h
//	Tv		 FJ๎๑ฬว
//	์ฌา	 Fษกๅๅ
//	XVL^	 F2024/02/17	21:40	Rgวม
//ธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถฒ

// =-=-= CN[hK[h =-=-=
#ifndef _____CAMERA_MANAGER_H_____
#define _____CAMERA_MANAGER_H_____

// =-=-= CN[h =-=-=
#include "CameraBase.h"
#include "SingletonsMng.hxx"

/// @brief Jฬ๎๑๐วท้
/// @brief ฅฃฅฃฅฃ VOgลท ฅฃฅฃฅฃ
class CameraManager final :public Singleton<CameraManager>
{
	friend class Singleton<CameraManager>;
public:
	void SetMainCamera(CameraBase*);
	CameraBase* GetMainCamera();

private:
	CameraManager();
	~CameraManager();
	CameraBase* m_pMainCamera;
};

#endif // !_____CAMERA_MANAGER_H_____