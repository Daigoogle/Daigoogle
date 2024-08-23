//	ファイル名：CameraManager.h
//	概要		 ：カメラ情報の管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/17	21:40	コメント追加
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____CAMERA_MANAGER_H_____
#define _____CAMERA_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include "CameraBase.h"
#include "SingletonsMng.hxx"

/// @brief カメラの情報を管理する
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class CameraManager final :public Singleton<CameraManager>
{
	friend class Singleton<CameraManager>;
public:
	void SetCamera(CameraBase*);
	CameraBase* GetMainCamera();

private:
	CameraManager();
	~CameraManager();
	CameraBase* m_pMainCamera;
};

#endif // !_____CAMERA_MANAGER_H_____