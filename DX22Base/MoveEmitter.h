#ifndef ___MOVE_EMITTER_H___
#define ___MOVE_EMITTER_H___

#include "Effect.h"
class MoveEmitter : public Emitter
{
public:
	MoveEmitter();
	~MoveEmitter();

protected:
	void Spawn(Particle* particle, const DirectX::XMFLOAT3& rootPos);

};

#endif
