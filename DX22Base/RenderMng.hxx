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
#include <unordered_map>
#include <queue>

class Render;

struct Vertex
{
	float pos[3];
	float uv[2];
};

enum MeshType
{
	MESH_plane = 0,
	MESH_Cube,
	MESH_Model,
};

class RenderMng: public Singleton<RenderMng>
{
	friend class Singleton<RenderMng>;
	using MeshBufIterator = std::unordered_map<uint32, MeshBuffer*>::const_iterator;
	using TextureIterator = std::unordered_map<uint32, Texture>::const_iterator;
public:
	RenderMng();
	~RenderMng();

	bool Init() override;
	void Update() override;

	void AddQueue(Render* render);

	MeshBuffer* GetMeshBuffer(std::string MeshPath);
	Texture* GetTexture(std::string TexturePath);
private:
	std::unordered_map<std::string, MeshBuffer*> m_MeshBuffer;
	std::unordered_map<std::string, Texture> m_MeshType;
	std::queue<Render*> m_RenderQueue;
};

#endif // !_____RenderMgr_HXX_____