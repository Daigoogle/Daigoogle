#include "Polyline.h"


VertexShader*	Polyline::m_pDefVS = nullptr;
PixelShader*	Polyline::m_pDefPS = nullptr;
int				Polyline::m_shaderRefCount = 0;


/*
* @brief コンストラクタ
* @param[in] maxVertices 最大頂点数
*/
Polyline::Polyline(int maxVertices)
	: m_useVtxCount(0)
	, m_pTexture(nullptr)
{
	// 頂点データ作成
	m_pVertices = new Vertex[maxVertices];

	// 頂点バッファ作成
	MeshBuffer::Description desc = {};
	desc.pVtx = m_pVertices;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = maxVertices;
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	desc.isWrite = true;
	m_pMesh = new MeshBuffer(desc);

	// シェーダー参照更新
	++m_shaderRefCount;
	if (m_shaderRefCount > 1)
	{
		SetVertexShader(nullptr);
		SetPixelShader(nullptr);
		return;
	}

	// デフォルトシェーダー作成
	const char* VS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.color = vin.color;
	return vout;
})EOT";
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

	m_pDefVS = new VertexShader();
	m_pDefVS->Compile(VS);
	m_pDefPS = new PixelShader();
	m_pDefPS->Compile(PS);
	SetVertexShader(nullptr);
	SetPixelShader(nullptr);
}

/*
* @brief デストラクタ
*/
Polyline::~Polyline()
{
	delete m_pMesh;
	delete[] m_pVertices;

	// シェーダー参照数更新
	-- m_shaderRefCount;
	if (m_shaderRefCount <= 0)
	{
		// シェーダー削除
		delete m_pDefVS;
		delete m_pDefPS;
	}
}

/*
* @brief 更新処理
*/
void Polyline::Update()
{
	// デフォルトでは処理なし
}

/*
* @brief 描画処理
*/
void Polyline::Draw()
{
	// 制御点と頂点データの更新
	for (UINT i = 0; i < m_lines.size(); ++i)
	{
		// 制御点の更新
		ControlPoints& points = m_lines[i].controlPoints;
		UpdateControlPoints(i, points);

		// 頂点の更新
		Vertex* pVtx = m_lines[i].ptr;
		ControlPoints::const_iterator it = points.cbegin();
		while (it != points.cend())
		{
			// 制御点に紐づく頂点に一旦値を設定
			UINT pointIdx = static_cast<UINT>(it - points.cbegin());
			pVtx[0].pos = it->pos;
			pVtx[0].color = it->color;
			pVtx[0].uv.x = m_lines[i].uvOffset.x + m_lines[i].uvScale.x * pointIdx / (points.size() - 1);
			pVtx[0].uv.y = m_lines[i].uvOffset.y;
			pVtx[1] = pVtx[0];

			// 前後の制御点から、頂点の配置位置を計算
			DirectX::XMVECTOR vPrev = DirectX::XMLoadFloat3(&(it - (pointIdx ? 1 : 0))->pos);
			DirectX::XMVECTOR vNext = DirectX::XMLoadFloat3(
				&(it + (pointIdx + 1 == points.size() ? 0 : 1))->pos);
			DirectX::XMVECTOR vNormal = DirectX::XMLoadFloat3(&it->normal);
			DirectX::XMVECTOR vDir = DirectX::XMVectorSubtract(vNext, vPrev);
			vNormal = DirectX::XMVector3Normalize(vNormal);
			vDir = DirectX::XMVector3Normalize(vDir);
			vDir = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(vNormal, vDir));
			vDir = DirectX::XMVectorScale(vDir, it->bold);
			DirectX::XMFLOAT3 dir;
			DirectX::XMStoreFloat3(&dir, vDir);
			pVtx[0].pos.x += dir.x;
			pVtx[0].pos.y += dir.y;
			pVtx[0].pos.z += dir.z;
			pVtx[1].pos.x -= dir.x;
			pVtx[1].pos.y -= dir.y;
			pVtx[1].pos.z -= dir.z;

			// 片頂点のuv値を調整
			pVtx[1].uv.y += m_lines[i].uvScale.y;

			// 次の制御点
			pVtx += 2;
			++it;
		}
	}

	// 縮退ポリゴン用の調整
	for (UINT i = 1; i < m_lines.size(); ++i)
	{
		Vertex* pVtx = m_lines[i].ptr;
		*(pVtx - 1) = *pVtx;
		*(pVtx - 2) = *(pVtx - 3);
	}

	// 更新された頂点データをもとにバッファを更新
	m_pMesh->Write(m_pVertices);

	// 描画
	m_pVS->Bind();
	m_pPS->Bind();
	m_pVS->WriteBuffer(0, m_matrix);
	m_pPS->SetTexture(0, m_pTexture);
	m_pMesh->Draw(m_useVtxCount);
}

void Polyline::SetView(DirectX::XMFLOAT4X4 view)
{
	m_matrix[0] = view;
}
void Polyline::SetProjection(DirectX::XMFLOAT4X4 proj)
{
	m_matrix[1] = proj;
}
void Polyline::SetVertexShader(VertexShader* vs)
{
	if (vs)
		m_pVS = vs;
	else
		m_pVS = m_pDefVS;
}
void Polyline::SetPixelShader(PixelShader* ps)
{
	if (ps)
		m_pPS = ps;
	else
		m_pPS = m_pDefPS;
}
void Polyline::SetTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
}

Polyline::LineID Polyline::AddLine(int controlPointNum)
{
	static const int SYUKUTAI = 2;

	// 残りの頂点数を計算
	MeshBuffer::Description desc = m_pMesh->GetDesc();
	if (desc.vtxCount < static_cast<UINT>(m_useVtxCount + controlPointNum * 2 + SYUKUTAI))
	{
		return LINE_NONE;
	}

	// 縮退ポリゴン用の頂点を追加するか確認
	if (!m_lines.empty())
	{
		m_useVtxCount += SYUKUTAI;
	}

	// ポリラインデータの生成
	Line line;
	line.controlPoints.resize(controlPointNum);
	InitControlPoints(static_cast<LineID>(m_lines.size()), line.controlPoints);
	line.uvScale = DirectX::XMFLOAT2(1.0f, 1.0f);
	line.uvOffset = DirectX::XMFLOAT2(0.0f, 0.0f);
	line.ptr = m_pVertices + m_useVtxCount;
	m_lines.push_back(line);

	// 使用済み頂点数の更新
	m_useVtxCount += controlPointNum * 2;
	return static_cast<LineID>(m_lines.size() - 1);
}

/*
* @brief 制御点の初期化
* @param[in] id ポリラインID
* @param[out] controlPoints ポリラインを制御する位置情報
*/
void Polyline::InitControlPoints(LineID id, ControlPoints& controlPoints)
{
	ControlPoints::iterator it = controlPoints.begin();
	while (it != controlPoints.cend())
	{
		it->pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		it->normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
		it->bold = 0.0f;
		it->color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		++it;
	}
}
