
#ifndef ___PLAYER_H____
#define ___PLAYER_H____

#include "Model.h"
#include "Shader.h"
#include "CameraBase.h"
#include "Texture.h"
#include "Effect.h"
#include "MoveEmitter.h"
#include "Transform.h"
#include "Component.h"

class CPlayer:public Component
{
public:
	CPlayer();
	~CPlayer();

	void Init()override;
	void Update()override;
	void UnInit()override;
	
	
	void Draw();

	//�J�����̐ݒ�
	void SetCamera(CameraBase* pCamera)
	{
		m_pCamera = pCamera;
	}

	//���ݒn�̎擾
	DirectX::XMFLOAT3 GetPos()
	{
		return m_pos;
	}
	Transform* GetTransform();

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;		//�J�����ւ̎Q��
	DirectX::XMFLOAT3 m_pos;	//�v���C���[�̈ʒu
	Texture* m_pShadow;
	Texture* m_pMarker;
	fVec3 m_oldPos;
	float m_Acseraration;
	Effect* m_pEffect;
	MoveEmitter* m_pMoveEmitter;
	
	Transform* m_Tf;
};

#endif // !___PLAYER_H____