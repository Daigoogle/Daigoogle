#include "SkyBoxComponent.h"
#include "SkyBoxManager.h" 
#include "BaseObject.h"
#include "TextureRegister.h"
#include "ShaderList.h" 

SkyBoxComponent::SkyBoxComponent()
	:m_Transform(nullptr), m_Color{ 1.0f,1.0f,1.0f,1.0f }, m_uvOffSet{ 0.0f,0.0f }, m_uvScale{ 1.0f,1.0f }
{

}

SkyBoxComponent::~SkyBoxComponent()
{}

void SkyBoxComponent::Init()
{
	// ---------�f�t�H���g���_�V�F�[�_�̃��[�h----------
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
	float4x4 view;
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
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;
	vout.color = color;
	return vout;
})EOT";
	m_Vs = new VertexShader();
	m_Vs->Compile(VS);

	// ---------�f�t�H���g�s�N�Z���V�F�[�_�̃��[�h----------
	const char* PS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET {
	float4 finalcolor = tex.Sample(samp, pin.uv) * pin.color;
	return finalcolor;
})EOT";
	m_Ps = new PixelShader();
	m_Ps->Compile(PS);

	// ---------�e�N�X�`���̃��������m��----------
	m_Texture = Singleton<TextureRegister>::GetInstance().LoadTexture("Assets/Texture/cube_map.png");
}

void SkyBoxComponent::Update()
{
	//// ---------�e�N�X�`���̃��[�h----------
	//if (m_textureLoadData.bIsNewLoad)
	//{
	//	;	//�e�N�X�`�������[�h
	//}
	//// ---------���_�V�F�[�_�̃��[�h----------
	//if (m_vtxShaderLoadData.bIsNewLoad)
	//{
	//	HRESULT hr = m_Vs->Load(m_vtxShaderLoadData.sPath.c_str());//���[�h
	//	if (FAILED(hr))
	//	{
	//		int a = 10;
	//	}
	//}
	//// ---------�s�N�Z���V�F�[�_�̃��[�h----------
	//if (m_pixelShaderLoadData.bIsNewLoad)
	//{
	//	m_pixelShader->Load(m_pixelShaderLoadData.sPath.c_str());	//���[�h
	//}

	// ---------�}�l�[�W���ɓo�^----------
	SkyBoxManager& manager = Singleton<SkyBoxManager>::GetInstance();
	manager.AddQueue(this);
}

void SkyBoxComponent::UnInit()
{

}

Transform* SkyBoxComponent::GetTransform()
{
	if (m_Transform == nullptr)
		m_Transform = GetBaseObject().GetComponent<Transform>();
	return m_Transform;
}

void SkyBoxComponent::LoadTexture(std::string sPath)
{
	m_Texture = Singleton<TextureRegister>::GetInstance().LoadTexture(sPath);
}

void SkyBoxComponent::SetVertexShader(std::string sPath)
{
	m_Vs = Singleton<ShaderList>::GetInstance().LoadVertexShader(sPath);
}

void SkyBoxComponent::SetPixelShader(std::string sPath)
{
	m_Ps = Singleton<ShaderList>::GetInstance().LoadPixelShader(sPath); 
}

void SkyBoxComponent::RegisterDataVertexShader(int nIndex, int nByte)
{
	// ----------�f�[�^�̗̈���쐬----------
	while (m_vtxShaderWriteDatas.size() < nIndex + 1)
	{
		std::shared_ptr<char[]>	byteData(new char[nByte]);
		m_vtxShaderWriteDatas.push_back(std::move(byteData));
	}
}

void SkyBoxComponent::RegisterDataPixelShader(int nIndex, int nByte)
{
	// ----------�f�[�^�̗̈���쐬----------
	while (m_pixelShaderWriteDatas.size() < nIndex + 1)
	{
		std::shared_ptr<char[]> byteData(new char[nByte]);
		m_pixelShaderWriteDatas.push_back(std::move(byteData));
	}
}

void SkyBoxComponent::WriteDataVertexShader(int nIndex, void* pData, int nByte)
{
	// ----------�f�[�^�̏�������----------
	void* pDest = reinterpret_cast<void*>(m_vtxShaderWriteDatas[nIndex].get());
	memcpy(pDest, pData, nByte);
}

void SkyBoxComponent::WriteDataPixelShader(int nIndex, void* pData, int nByte)
{
	// ----------�f�[�^�̏�������----------
	void* pDest = reinterpret_cast<void*>(m_pixelShaderWriteDatas[nIndex].get());
	memcpy(pDest, pData, nByte);
}