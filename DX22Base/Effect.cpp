#include "Effect.h"
#include "DirectXTex/TextureLoad.h"

//========================
//		パーティクル
//========================
Particle::Particle()
{
	Reset();
}
Particle::~Particle()
{
}
void Particle::Reset()
{
	life = 1.0f;
	pos.Reset();
	size.Reset();
	color.Reset();
	alpha.Reset();
	size.value = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	color.value = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	alpha.value.x = 1.0f;
}
void Particle::Update(float tick)
{
	if (!IsAlive())
	{
		return;
	}

	pos.Step();
	size.Step();
	color.Step();
	alpha.Step();
	life -= tick;
}
void Particle::Draw(DirectX::XMFLOAT4X4& matrix, Texture* pTexture)
{
	if (!IsAlive())
	{
		return;
	}

	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
		pos.value.x, pos.value.y, pos.value.z);
	DirectX::XMMATRIX inv = DirectX::XMLoadFloat4x4(&matrix);
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(inv * T));
	Sprite::SetWorld(world);
	Sprite::SetSize(DirectX::XMFLOAT2(size.value.x, size.value.y));
	Sprite::SetTexture(pTexture);
	Sprite::SetColor(DirectX::XMFLOAT4(
		color.value.x, color.value.y, color.value.z, alpha.value.x));
	Sprite::Draw();
}
bool Particle::IsAlive()
{
	return life > 0.0f;
}

//========================
//		エミッター
//========================
Emitter::Emitter(const char* textureFile, Description desc)
	: m_defDesc(desc), m_time(0.0f), m_life(0.0f)
{
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create(textureFile)))
	{
		MessageBox(NULL, textureFile, "Effect Error", MB_OK);
	}
}
Emitter::~Emitter()
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}
void Emitter::Update(const DirectX::XMFLOAT3& pos, float tick)
{
	// 既存パーティクルの更新
	Particles::iterator it = m_particles.begin();
	while (it != m_particles.end())
	{
		it->Update(tick);
		++it;
	}

	// 時間更新
	m_time += tick;
	m_life -= tick;

	// 新規パーティクル生成
	if (m_defDesc.interval <= m_time && IsPlay())
	{
		Create(pos);
		m_time -= m_defDesc.interval;
	}
}

void Emitter::Draw(DirectX::XMFLOAT4X4& matrix)
{
	std::vector<Particle>::iterator it = m_particles.begin();
	while (it != m_particles.end())
	{
		it->Draw(matrix, m_pTexture);
		++it;
	}
}

void Emitter::Play()
{
	m_time = 0.0f;
	m_life = m_defDesc.lifeTime;
}

bool Emitter::IsPlay()
{
	return m_life > 0.0f;
}

void Emitter::Create(const DirectX::XMFLOAT3& pos)
{
	Particles::iterator particleIt = m_particles.begin();
	for(int i = 0; i < m_defDesc.spawnNum; ++ i)
	{
		// 使用済みパーティクルの探索
		while (particleIt != m_particles.end())
		{
			if (!particleIt->IsAlive())
			{
				break;
			}
			++particleIt;
		}

		// パーティクルの新規追加
		if (particleIt == m_particles.end())
		{
			m_particles.push_back(Particle());
			particleIt = m_particles.end() - 1;
		}

		// パーティクルの生成
		particleIt->Reset();
		Spawn(particleIt._Ptr, pos);
	}
}

//========================
//		エフェクト
//========================
Effect::Effect()
	: m_pos(0.0f, 0.0f, 0.0f)
{
	DirectX::XMStoreFloat4x4(&m_billboard, DirectX::XMMatrixIdentity());
}
Effect::~Effect()
{
	m_pEmitters.clear();
}
void Effect::Update()
{
	Emitters::iterator it = m_pEmitters.begin();
	while (it != m_pEmitters.end())
	{
		(*it)->Update(m_pos, 1.0f / 60.0f);
		++it;
	}
}
void Effect::Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj)
{
	Sprite::SetView(view);
	Sprite::SetProjection(proj);
	Emitters::iterator it = m_pEmitters.begin();
	while (it != m_pEmitters.end())
	{
		(*it)->Draw(m_billboard);
		++it;
	}
}

void Effect::Play()
{
	Emitters::iterator it = m_pEmitters.begin();
	while (it != m_pEmitters.end())
	{
		(*it)->Play();
		++it;
	}
}
bool Effect::IsPlay()
{
	Emitters::iterator it = m_pEmitters.begin();
	while (it != m_pEmitters.end())
	{
		if ((*it)->IsPlay())
		{
			return true;
		}
		++it;
	}
	return false;
}
void Effect::AddEmitter(Emitter* pEmitter)
{
	m_pEmitters.push_back(pEmitter);
}
void Effect::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}
void Effect::SetBillboardMatrix(DirectX::XMFLOAT4X4& billboard)
{
	m_billboard = billboard;
}