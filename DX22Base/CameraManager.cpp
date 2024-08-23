#include "CameraManager.h"
#include "CameraDebug.h"
#include "BaseObjectManager.h"
#include "SceneManager.h"
#include "Transform.h"

CameraManager::CameraManager()
	: Singleton(UPDATE_ORDER::NO_UPDATE)
	, m_pMainCamera(nullptr)
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::SetCamera(CameraBase* cam)
{
	m_pMainCamera = cam;
}

CameraBase* CameraManager::GetMainCamera()
{
	//if (m_pMainCamera == nullptr)
	//{
	//	BaseObject cam = ObjectManager::Make(Singleton<SceneManager>::GetInstance().GetScene());
	//	cam.AddComponent<Transform>();
	//	m_pMainCamera = cam.AddComponent<CameraDebug>();
	//}
	return m_pMainCamera;
}
