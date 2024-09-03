//	ファイル名	：RenderMgr.hxx
//	  概  要		：
//	作	成	者	：daigo
//	 作成日時	：2024/06/11 20:35:52
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____RenderMgr_HXX_____
#define _____RenderMgr_HXX_____

// =-=-= インクルード部 =-=-=
#include <unordered_map>
#include <queue>
#include "Vectors.hxx"
#include "SingletonsMng.hxx"
#include "MeshBuffer.h"
#include "Model.h"
#include "Shader.h"

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
};

class RenderMng: public Singleton<RenderMng>
{
	friend class Singleton<RenderMng>;
public:
	/// @brief 
	/// @return 
	bool Init() override;
	void Update() override;

	void AddQueue(Render* render);

	MeshBuffer* GetMeshBuffer(MeshType type);
	Model* GetModel(const std::string& Path);
	Texture* GetTexture(const std::string& Path);
	VertexShader* GetVertexShader(const std::string& Path);
	PixelShader* GetPixelShader(const std::string& Path);
private:
	RenderMng();
	~RenderMng();

	std::unordered_map<std::string, Model*> m_Model;
	std::unordered_map<std::string, Texture*> m_Texture;
	std::unordered_map<std::string, VertexShader*> m_VertexShader;
	std::unordered_map<std::string, PixelShader*> m_PixelShader;
	std::array<MeshBuffer*, 2> m_MeshBuffer;
	std::queue<Render*> m_RenderQueue;
};

#endif // !_____RenderMgr_HXX_____