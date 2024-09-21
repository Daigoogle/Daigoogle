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
#include "ModelData.h"
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

enum LAYER_TYPE
{
	FRONT = 0,
	MIDDLE,
	LAST,
};

class RenderMng: public Singleton<RenderMng>
{
	friend class Singleton<RenderMng>;
public:
	/// @brief 
	/// @return 
	bool Init() override;
	void Update() override;

	void AddQueue(Render* render, LAYER_TYPE layer);

	MeshBuffer* GetMeshBuffer(MeshType type);
	MODEL* GetModel(const std::string& Path);
	Texture* GetTexture(const std::string& Path);
	VertexShader* GetVertexShader(const std::string& Path);
	PixelShader* GetPixelShader(const std::string& Path);
private:
	RenderMng();
	~RenderMng();

	std::unordered_map<std::string, std::unique_ptr<MODEL>> m_Model;
	std::unordered_map<std::string, std::unique_ptr<Texture>> m_Texture;
	std::unordered_map<std::string, std::unique_ptr<VertexShader>> m_VertexShader;
	std::unordered_map<std::string, std::unique_ptr<PixelShader>> m_PixelShader;
	std::array<std::unique_ptr<MeshBuffer>, 2> m_MeshBuffer;

	std::array<std::queue<Render*>,3> m_RenderQueue;
	bool m_Swap;

	std::mutex m_Mutex;
};

#endif // !_____RenderMgr_HXX_____