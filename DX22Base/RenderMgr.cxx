#include "RenderMgr.hxx"
#include "ThreadPoolMng.hxx"

RenderMgr::RenderMgr()
	: Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

RenderMgr::~RenderMgr()
{

}

bool RenderMgr::Init()
{
	return true;
}

void RenderMgr::Update()
{
	while (!m_RenderQueue.empty()) {
		Render* render = m_RenderQueue.front();
		m_RenderQueue.pop();
		ThreadPoolMng::GetInstance().AddPool([render]() {render->Draw();});
	}
}