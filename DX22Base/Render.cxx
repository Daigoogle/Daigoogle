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