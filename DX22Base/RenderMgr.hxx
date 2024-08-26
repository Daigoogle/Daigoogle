//	�t�@�C����	�FRenderMgr.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/11 20:35:52
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____RenderMgr_HXX_____
#define _____RenderMgr_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Vectors.hxx"
#include "SingletonsMng.hxx"
#include "MeshBuffer.h"
#include "Render.hxx"
#include <unordered_map>
#include <queue>

class RenderMgr: public Singleton<RenderMgr>
{
	friend class Singleton<RenderMgr>;
public:
	RenderMgr();
	~RenderMgr();

	bool Init() override;
	void Update() override;

	void AddQueue(Render* render);

private:
	std::unordered_map<uint32, MeshBuffer*> m_MeshBuffer;
	std::queue<Render*> m_RenderQueue;
};

#endif // !_____RenderMgr_HXX_____