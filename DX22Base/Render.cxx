#include "Render.hxx"
#include "RenderMgr.hxx"

Render::Render()
{

}

Render::~Render()
{

}

void Render::Update()
{
	RenderMgr::GetInstance().AddQueue(this);
}