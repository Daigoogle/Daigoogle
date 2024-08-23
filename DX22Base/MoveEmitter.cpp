#include "MoveEmitter.h"

MoveEmitter::MoveEmitter():
	Emitter("Assets/Texture/Smoke.png",
		{3,0.03f,0.1f})
{

}

MoveEmitter::~MoveEmitter()
{

}

void MoveEmitter::Spawn(Particle * particle, const DirectX::XMFLOAT3 & rootPos)
{
	particle->pos.value = rootPos;
	particle->pos.value.x += (rand() % 3 - 1) * 0.1f;
	particle->pos.add.y = 0.01f;

	particle->size.value.x = 0.5f;
	particle->size.value.y = 0.5f;
	particle->size.add.x = 0.1f;
	particle->size.add.y = 0.1f;
	particle->alpha.add.x = -0.05f;
	particle->alpha.add.y = -0.05f;
	particle->life = 0.5f;
}
