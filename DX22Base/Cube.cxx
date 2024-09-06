#include "Cube.hxx"
#include "RenderMng.hxx"

Cube::Cube()
{
}

Cube::~Cube()
{

}

void Cube::Draw()
{
	RenderMng::GetInstance().AddQueue(this);
}

bool Cube::Init()
{
	m_pMeshBuffer = RenderMng::GetInstance().GetMeshBuffer(MESH_Cube);
	Render::InitSetting();
	return true;
}