#include "RenderMng.hxx"
#include "Render.hxx"
#include "ThreadPoolMng.hxx"
#include "DirectX11SetUp.h"

RenderMng::RenderMng()
	: Singleton(UPDATE_ORDER::LAST_UPDATE)
{

}

RenderMng::~RenderMng()
{

}

bool RenderMng::Init()
{
	// ----------メッシュバッファの初期化---------
	Vertex vtx[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {1.0f, 1.0f}},
	};

	MeshBuffer::Description desc = m_MeshBuffer["Plane"]->GetDesc();
	desc.pVtx = vtx;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	// 元データの 
	Vertex vtx[] = {
		//-z面
		{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ 0.5f, 0.5f,-0.5f},{1.0f,0.0f}},//1
		{{-0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//2
		{{ 0.5f,-0.5f,-0.5f},{1.0f,1.0f}},//3
		//z
		{{-0.5f, 0.5f,0.5f},{0.0f,0.0f}},//4
		{{ 0.5f, 0.5f,0.5f},{1.0f,0.0f}},//5
		{{-0.5f,-0.5f,0.5f},{0.0f,1.0f}},//6
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//7
		//-x
		{{ -0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ -0.5f, 0.5f,0.5f},{1.0f,0.0f}},//4
		{{ -0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//2
		{{ -0.5f,-0.5f,0.5f},{1.0f,1.0f}},//6
		//x
		{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//1
		{{ 0.5f, 0.5f,0.5f},{1.0f,0.0f}},//5
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//3
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//7
		//-y
		{{ -0.5f, -0.5f,-0.5f},{0.0f,0.0f}},//2
		{{ -0.5f, -0.5f,0.5f},{1.0f,0.0f}},//6
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},//3
		{{ 0.5f,-0.5f,0.5f},{1.0f,1.0f}},//5

		//y
		{{ -0.5f, 0.5f,-0.5f},{0.0f,0.0f}},//0
		{{ -0.5f, 0.5f,0.5f},{1.0f,0.0f}},//4
		{{ 0.5f,0.5f,-0.5f},{0.0f,1.0f}},//1
		{{ 0.5f,0.5f,0.5f},{1.0f,1.0f}},//5
	};

	int idx[] = {
		0,1,2,		1,3,2,		//-Z面
		6,5,4,		6,7,5,		//Z面
		10,9,0,		10,11,9,	//-x
		12,13,14,	13,15,14,	//x
		18,17,16,	18,19,17,	//-y
		0,21,22,	21,23,22,	//y

	};
	// バッファの作成
	MeshBuffer::Description desc = m_MeshBuffer["Cube"]->GetDesc();
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);
	desc.vtxSize = 20;//20;
	desc.pIdx = idx;
	desc.idxCount = 36;
	desc.idxSize = sizeof(int);//4;
	desc.topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


	return true;
}

void RenderMng::Update()
{

	DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	Dx11.BeginDraw();

	RenderTarget* pRT = Dx11.GetDefaultRTV();//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDS = Dx11.GetDefaultDSV();//DeapthStencilViewの取得

	Dx11.SetRenderTargets(1, &pRT, pDS);

	while (!m_RenderQueue.empty()) {
		Render* render = m_RenderQueue.front();
		m_RenderQueue.pop();
		//ThreadPoolMng::GetInstance().AddPool([render]() {render->Draw();});
		render->Draw();
	}
		
	Dx11.EndDraw();
}

void RenderMng::AddQueue(Render* render)
{
	m_RenderQueue.push(render);
}

MeshBuffer* RenderMng::GetMeshBuffer(std::string MeshPath)
{
	return m_MeshBuffer[MeshPath];
}

Texture* RenderMng::GetTexture(std::string TexturePath)
{
	return &m_MeshType[TexturePath];
}