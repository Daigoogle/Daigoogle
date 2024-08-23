#include "TrailEffeect.h"

TrailEffect::TrailEffect(CPlayer * pPlayer)
	:m_pPlayer(pPlayer)
{
	m_oldPos = m_pPlayer->GetPos();
}

TrailEffect::~TrailEffect()
{
}

void TrailEffect::UpdateControlPoints(LineID id, ControlPoints & controlPoints)
{
	//毎フレーム、ポリラインの幅を少しずつ小さくする
	ControlPoints::iterator it = controlPoints.begin();
	while (it != controlPoints.end())
	{
		it->bold *= 0.85f;
		++it;
	}
}
