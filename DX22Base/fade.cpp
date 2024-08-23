#include "fade.h"
#include "easing.h"
#include <stdlib.h>
#include "TextureRegister.h"

Fade::Fade()
	: Singleton(UPDATE_ORDER::LAST_UPDATE)
{

}

Fade::~Fade()
{
	if (m_Transform != nullptr)
	{
		delete m_Transform;
		m_Transform = nullptr;
	}
	m_vertexShader.release();
	m_pixelShader.release();
	m_meshBuffer.release();
}

bool Fade::Init()
{
	// ----------メッシュバッファの初期化----------
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};

	Vertex vtx[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {1.0f, 1.0f}},
	};

	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_meshBuffer = std::make_unique<MeshBuffer>(desc);

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
	m_texture = TextureRegister::GetInstance().LoadTexture("Assets/Texture/defalt.png");

	m_Transform = new Transform;
	m_Transform->SetWorldScale({ 100.0f, 100.0f, 100.0f });
	//m_FadeObj = new Sprite2DTip;
	//m_FadeObj->Init();
	//m_FadeObj->LoadTexture("Assets/Texture/defalt.png");
	//m_FadeObj->SetColor({ 0.0f,0.0f,0.0f,m_alpha });
	//m_FadeObj->GetTransform()->SetLocalScale({1920.0f, 1080.0f, 1.0f});
	//m_FadeObj->GetTransform()->SetWorldPosition({ 0.0f,0.0f,999.0f });
	//m_alpha = 0.0f;
	return true;
}

void Fade::Update()
{
	m_bEndFlg = false;
	if (m_bOut)
	{
		m_color = { 0.0f,0.0f,0.0f,Easing::InOutSine(m_alpha) };
		if (m_alpha > 1.0f)
		{
			m_alpha = 1.0f;
			m_bOut = false;
			m_bIn = false;
			m_bEndFlg = true;
		}
		m_alpha += 0.01f;
	}
	else if (m_bIn)
	{
		m_color = { 0.0f,0.0f,0.0f,Easing::InOutSine(m_alpha) };
		if (m_alpha < 0.0f)
		{
			m_alpha = 0.0f;
			m_bOut = false;
			m_bIn = false;
			m_bEndFlg = true;
		}
		m_alpha -= 0.01f;
	}
		//m_alpha = 0.0f;
}
void Fade::Draw()
{
	// 深度バッファを切る
	DirectX11SetUp& Dx11 = Singleton<DirectX11SetUp>::GetInstance();

	RenderTarget* pRT = Dx11.GetDefaultRTV();//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDS = Dx11.GetDefaultDSV();//DepthStencilViewの取得

	Dx11.SetRenderTargets(1, &pRT, nullptr);



	// パラメータを取得
	DirectX::XMFLOAT4X4	vertexMats[2];
	vertexMats[0] = m_Transform->GetWorldMatrix();
	VertexShader* pVtxShader = m_vertexShader.get();
	PixelShader* pPixelShader = m_pixelShader.get();
	fVec4		color = m_color;
	fVec2		uvOffset = m_uvOffSet;
	fVec2		uvScale = m_uvScale;
	std::vector<std::shared_ptr<char[]>>& vtxShaderData = m_vtxShaderWriteDatas;
	std::vector<std::shared_ptr<char[]>>& pixelShaderData = m_pixelShaderWriteDatas;
	Texture* pTexture = m_texture;

	// プロジェクション行列の処理
	DirectX::XMStoreFloat4x4(&vertexMats[1],
		DirectX::XMMatrixOrthographicLH(
			1.0f, 1.0f, 0.0f, 1.0f
		)
	);

	// 頂点シェーダの処理
	float afVtxInfos[] = {
		uvOffset.x,
		uvOffset.y,
		uvScale.x,
		uvScale.y,
		color.x,
		color.y,
		color.z,
		color.w
	};

	pVtxShader->WriteBuffer(0, &vertexMats);	//行列を書き込み
	pVtxShader->WriteBuffer(1, afVtxInfos);		//UVを書き込み
	int nNoInfo = 2;
	for (int nCntInfo = 0; nCntInfo < vtxShaderData.size(); nCntInfo++)
	{
		pVtxShader->WriteBuffer(nNoInfo, vtxShaderData[nCntInfo].get());
		nNoInfo++;
	}
	pVtxShader->Bind();

	// ピクセルシェーダの処理
	for (int nCntInfo = 0; nCntInfo < pixelShaderData.size(); nCntInfo++)
	{
		pPixelShader->WriteBuffer(nCntInfo, pixelShaderData[nCntInfo].get());
	}
	pPixelShader->SetTexture(0, pTexture);
	pPixelShader->Bind();

	// メッシュバッファの処理
	m_meshBuffer->Draw();

	Dx11.SetRenderTargets(1, &pRT, pDS);// 深度バッファを戻す
}
void Fade::InStart()
{
	m_alpha = 1.0f;
	m_bIn = true;
}
void Fade::OutStart()
{
	m_alpha = 0.0f;
	m_bOut = true;
}
float Fade::GetAlpha()
{
	return m_alpha;
}
bool Fade::GetEnd()
{
	return m_bEndFlg;
}