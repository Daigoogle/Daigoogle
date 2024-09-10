#include "RenderMng.hxx"
#include "Render.hxx"
#include "ThreadPoolMng.hxx"
#include "DirectX11SetUp.h"
#include "DebugRestriction.hxx"


RenderMng::RenderMng()
	: Singleton(UPDATE_ORDER::LAST_UPDATE)
{

}

RenderMng::~RenderMng()
{
	m_Model.clear();
	m_Texture.clear();
	m_VertexShader.clear();
	m_PixelShader.clear();
	for (auto& elem : m_MeshBuffer)
	{
		//delete elem;
		//elem = nullptr;
	}
}

bool RenderMng::Init()
{
	// ----------メッシュバッファの初期化---------
	Vertex vtx0[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {1.0f, 1.0f}},
	};

	MeshBuffer::Description desc0;
	desc0.pVtx = vtx0;
	desc0.vtxSize = sizeof(Vertex);
	desc0.vtxCount = _countof(vtx0);
	desc0.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_MeshBuffer[MeshType::MESH_plane] = new MeshBuffer(desc0);

	// 元データの 
	Vertex vtx1[] = {
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

	int idx1[] = {
		0,1,2,		1,3,2,		//-Z面
		6,5,4,		6,7,5,		//Z面
		10,9,0,		10,11,9,	//-x
		12,13,14,	13,15,14,	//x
		18,17,16,	18,19,17,	//-y
		0,21,22,	21,23,22,	//y

	};
	// バッファの作成
	MeshBuffer::Description desc1;
	desc1.pVtx = vtx1;
	desc1.vtxCount = _countof(vtx1);
	desc1.vtxSize = 20;
	desc1.pIdx = idx1;
	desc1.idxCount = 36;
	desc1.idxSize = sizeof(int);
	desc1.topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_MeshBuffer[MeshType::MESH_Cube] = new MeshBuffer(desc1);

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

MeshBuffer* RenderMng::GetMeshBuffer(MeshType type)
{
	return NullptrCheck(m_MeshBuffer[type]);
}

Model* RenderMng::GetModel(const std::string& ModelPath)
{
	if (!m_Model.count(ModelPath)) {
		m_Model[ModelPath] = new Model;
		FalseCheck(m_Model[ModelPath]->Load(ModelPath.c_str(), 1.0f, Model::XFlip));
	}
	return NullptrCheck(m_Model[ModelPath]);
}

Texture* RenderMng::GetTexture(const std::string& TexturePath)
{
	if (!m_Texture.count(TexturePath)) {
		m_Texture[TexturePath] = new Texture;
		HResultCheck( m_Texture[TexturePath]->Create(TexturePath.c_str()));
	}
	return NullptrCheck( m_Texture[TexturePath]);
}

VertexShader* RenderMng::GetVertexShader(const std::string& VertexShaderPath)
{
	if (!m_VertexShader.count(VertexShaderPath))
	{
		m_VertexShader[VertexShaderPath] = new VertexShader();
		HResultCheck(m_VertexShader[VertexShaderPath]->Load(VertexShaderPath.c_str()));
	}
	return NullptrCheck(m_VertexShader[VertexShaderPath]);
}

PixelShader* RenderMng::GetPixelShader(const std::string& PixelShaderPath)
{
	if (!m_PixelShader.count(PixelShaderPath))
	{
		m_PixelShader[PixelShaderPath] = new PixelShader();
		HResultCheck(m_PixelShader[PixelShaderPath]->Load(PixelShaderPath.c_str()));
	}
	return NullptrCheck(m_PixelShader[PixelShaderPath]);
}