#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <vector>
#include "Sprite.h"

class Particle
{
public:
	Particle();
	~Particle();
	void Reset();
	virtual void Update(float tick);
	void Draw(DirectX::XMFLOAT4X4& billboard, Texture* pTexture);
	bool IsAlive();

public:
	struct Param
	{
		DirectX::XMFLOAT3 value;
		DirectX::XMFLOAT3 add;
		DirectX::XMFLOAT3 accele;

		void Reset()
		{
			value = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			add = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			accele = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}
		void Step()
		{
			add.x *= accele.x;
			add.y *= accele.y;
			add.z *= accele.z;
			value.x += add.x;
			value.y += add.y;
			value.z += add.z;
		}
	};
	Param pos;
	Param size;
	Param color;
	Param alpha;
	float life;
};

class Emitter
{
private:
	using Particles = std::vector<Particle>;
public:
	struct Description
	{
		int spawnNum; // 1âÒÇÃê∂ê¨êî
		float interval; // ê∂ê¨ä‘äu
		float lifeTime; // ê∂ë∂éûä‘
	};

public:
	Emitter(const char* textureFile, Description desc);
	virtual ~Emitter();
	void Update(const DirectX::XMFLOAT3& pos, float tick);
	void Draw(DirectX::XMFLOAT4X4& billboard);

	void Play();
	bool IsPlay();
	
private:
	void Create(const DirectX::XMFLOAT3& pos);

protected:
	virtual void Spawn(Particle* particle, const DirectX::XMFLOAT3& rootPos) = 0;

private:
	Particles m_particles;
	Texture* m_pTexture;
	Description m_defDesc;
	float m_time;
	float m_life;
};

class Effect
{
private:
	using Emitters = std::vector<Emitter*>;

public:
	Effect();
	~Effect();
	void Update();
	void Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);

	void Play();
	bool IsPlay();
	void AddEmitter(Emitter* pEmitter);
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetBillboardMatrix(DirectX::XMFLOAT4X4& billboard);
private:
	Emitters m_pEmitters;
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT4X4 m_billboard;
};

#endif // __EFFECT_H__