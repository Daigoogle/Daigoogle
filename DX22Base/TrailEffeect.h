#ifndef ___TRAIL_EFFECT_H___
#define ___TRAIL_EFFECT_H___

#include "Polyline.h"
#include "Player.h"

//�v���C���[��ǂ�������G�t�F�N�g
class TrailEffect :public Polyline
{
public:
	TrailEffect(CPlayer* pPlayer);
	~TrailEffect();


protected:
	//�|�����C���̐���_���X�V
	virtual void UpdateControlPoints(
		LineID id, ControlPoints& controlPoints) final;

private:
	CPlayer* m_pPlayer;
	DirectX::XMFLOAT3 m_oldPos;

};


#endif // !___TRAIL_EFFECT_H___

