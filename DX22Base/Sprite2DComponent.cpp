#include "Sprite2DComponent.h"
#include "Sprite2DManager.h"
#include "TextureRegister.h"
#include "BaseObject.h"
#include "PutLog.h"

Sprite2DComponent::Sprite2DComponent(void)
	: m_Transform(nullptr)
	, m_color{ 1.0f, 1.0f, 1.0f, 1.0f }
	, m_uvOffSet{ 0.0f, 0.0f }
	, m_uvScale{ 1.0f, 1.0f }
	, m_texture(nullptr)
{
	//m_Transform.reset(new Transform);
}

void Sprite2DComponent::Init(void)
{
	// ---------デフォルト頂点シェーダのロード----------
	const char* VS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float2 uvPos;
	float2 uvScale;
	float4 color;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;
	vout.color = color;
	return vout;
})EOT";
	m_vertexShader = std::make_unique<VertexShader>();
	m_vertexShader->Compile(VS);

	// ---------デフォルトピクセルシェーダのロード----------
	const char* PS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET {
	return tex.Sample(samp, pin.uv) * pin.color;
})EOT";
	m_pixelShader = std::make_unique<PixelShader>();
	m_pixelShader->Compile(PS);

	// ---------テクスチャのメモリを確保----------
	if(m_texture == nullptr)
		m_texture = Singleton<TextureRegister>::GetInstance().LoadTexture("Assets/Texture/defalt.png");

	// ---------- トランスフォームを取得 ----------
	m_Transform = GetBaseObject().GetComponent<Transform>();
	if (m_Transform == nullptr)
		Error("Not Component : Transform\n to Sprite2DTip");

	return;
}

void Sprite2DComponent::UnInit()
{

}

void Sprite2DComponent::Update(void)
{
	// ---------マネージャに登録----------
	Singleton<Sprite2DManager>::GetInstance().AddQueue(this);
}

void Sprite2DComponent::LoadTexture(std::string sPath)
{
	// ---------テクスチャのロード----------
	m_texture = Singleton<TextureRegister>::GetInstance().LoadTexture(sPath);
}

void Sprite2DComponent::SetVertexShader(std::string sPath)
{
	// ---------頂点シェーダのロード----------
	m_vertexShader.reset();									//メモリ解放
	m_vertexShader = std::make_unique<VertexShader>();		//メモリ確保
	m_vertexShader->Load(sPath.c_str());//ロード
}

void Sprite2DComponent::SetPixelShader(std::string sPath)
{
	// ---------ピクセルシェーダのロード----------
	m_pixelShader.reset();										//メモリ解放
	m_pixelShader = std::make_unique<PixelShader>();			//メモリ確保
	m_pixelShader->Load(sPath.c_str());	//ロード
}

void Sprite2DComponent::RegisterDataVertexShader(int nIndex, int nByte)
{
	// ----------データの領域を作成----------
	while (m_vtxShaderWriteDatas.size() < nIndex + 1)
	{
		std::shared_ptr<char[]>	byteData(new char[nByte]);
		m_vtxShaderWriteDatas.push_back(std::move(byteData));
	}
}


void Sprite2DComponent::RegisterDataPixelShader(int nIndex, int nByte)
{
	// ----------データの領域を作成----------
	while (m_pixelShaderWriteDatas.size() < nIndex + 1)
	{
		std::shared_ptr<char[]> byteData(new char[nByte]);
		m_pixelShaderWriteDatas.push_back(std::move(byteData));
	}
}

void Sprite2DComponent::WriteDataVertexShader(int nIndex, void* pData, int nByte)
{
	// ----------データの書き込み----------
	void* pDest = reinterpret_cast<void*>(m_vtxShaderWriteDatas[nIndex].get());
	memcpy(pDest, pData, nByte);
}

void Sprite2DComponent::WriteDataPixelShader(int nIndex, void* pData, int nByte)
{
	// ----------データの書き込み----------
	void* pDest = reinterpret_cast<void*>(m_pixelShaderWriteDatas[nIndex].get());
	memcpy(pDest, pData, nByte);
}