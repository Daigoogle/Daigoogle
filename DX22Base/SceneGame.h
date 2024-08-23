#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
#include "SceneBase.h"
#include "Model.h"
#include "Shader.h"
#include "CameraBase.h"
#include "Player.h"
#include "ItemUI.h"
#include "CubeCollisionToDirectManager.h"
#include "NumSprite2D.h"
#include "CubeComponent.h"
#include "Sprite3DComponent.h"

enum CameraKind {
	CAM_PLAYER,	//�v���C���[�J����
	CAM_DBG,	//�f�o�b�N�J����
	MAX_CAM		//�J�����ő吔
};

class SceneGame :
	public SceneBase
{
public:
	SceneGame()
		:m_pCamera(),m_pModel(nullptr),m_pPlayer(nullptr),m_pVS(nullptr),
		m_Item(),m_mainCamera(CAM_PLAYER)
	{}

	~SceneGame(){}

	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera[MAX_CAM];
	CPlayer* m_pPlayer;			//������p��
	CameraKind m_mainCamera;	//�\���ɗ��p���Ă���J�����̎��
	ItemUI m_Item;
	fVec3 m_BlockPos;

	bool g_bNext;
	bool m_EndFlg;
	CubeCollisionToDirectComponent* g_CubeColl;
	CubeCollisionToDirectComponent* g_PlayerColl;
	CubeComponent** g_pCubeS;
	CubeCollisionToDirectComponent* g_pCCollS;
	Sprite3DComponent* g_WG;
	NumSprite2D* g_NumBer;

};



#endif // __SCENE_GAME_H__