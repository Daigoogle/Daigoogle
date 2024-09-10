#include "Render.hxx"
#include "RenderMng.hxx"

Render::Render()
	: m_Color({ 1.0f, 1.0f, 1.0f, 1.0f })
	, m_uvOffSet({0.0f,0.0f})
	, m_uvScale({ 1.0f,1.0f })
	, m_pMeshBuffer(nullptr)
	, m_pTexture(nullptr)
	, m_PixelShader(nullptr)
	, m_VertexShader(nullptr)
{

}

Render::~Render()
{

}

void Render::InitSetting()
{
	if (!m_VertexShader) {
		m_VertexShader = RenderMng::GetInstance().GetVertexShader("Assets/Shader/DefaltModel_VS.cso");
	}
	if (!m_PixelShader) {
		m_PixelShader = RenderMng::GetInstance().GetPixelShader("Assets/Shader/DefaltModel_PS.cso");
	}
	if (!m_pTexture) {
		m_pTexture = RenderMng::GetInstance().GetTexture("Assets/Texture/defalt.png");
	}
}

void Render::SetTexture(const std::string& Path)
{
	m_pTexture = RenderMng::GetInstance().GetTexture(Path);
}
void Render::SetPixelShader(const std::string& Path)
{
	m_PixelShader = RenderMng::GetInstance().GetPixelShader(Path);
}
void Render::SetVertexShader(const std::string& Path)
{
	m_VertexShader = RenderMng::GetInstance().GetVertexShader(Path);
}

void Render::Update()
{
	RenderMng::GetInstance().AddQueue(this);
}