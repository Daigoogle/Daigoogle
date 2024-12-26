//	ファイル名	：Render.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/11 20:42:52
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Render_HXX_____
#define _____Render_HXX_____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"
#include "Shader.h"

class RenderMng;
class MeshBuffer;
enum LAYER_TYPE;

struct VERTEX_3D
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT2 TexCoord;
};

struct MATERIAL
{
	MATERIAL()	// マテリアル未設定モデル対策
	{
		Diffuse = Ambient = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		Specular = Emission = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		Shininess = 1.0f;
		TextureEnable = false;
		Dummy[0] = Dummy[1] = 0.0f;
	}

	DirectX::XMFLOAT4	Ambient;
	DirectX::XMFLOAT4	Diffuse;
	DirectX::XMFLOAT4	Specular;
	DirectX::XMFLOAT4	Emission;
	float				Shininess;
	BOOL				TextureEnable;
	float				Dummy[2];
};

struct LIGHT
{
	BOOL				Enable;
	BOOL				Dummy[3];
	DirectX::XMFLOAT4	Direction;
	DirectX::XMFLOAT4	Diffuse;
	DirectX::XMFLOAT4	Ambient;
};

/// @brief 描画物の基底クラス。単体での使用不可
class Render :public Component
{
	friend class RenderMng;
public:
	Render();
	virtual ~Render();

	void SetTexture(const std::string& Path);
	void SetPixelShader(const std::string& Path);
	void SetVertexShader(const std::string& Path);
	void SetLayer(LAYER_TYPE layer);

	void Update()override;
protected:
	virtual bool Init() = 0;
	virtual void Draw() = 0;

	void InitSetting();

	Transform* m_Transform;
	LAYER_TYPE m_Layer;

	MeshBuffer* m_pMeshBuffer;
	Texture* m_pTexture;

	PixelShader* m_PixelShader;
	VertexShader* m_VertexShader;

	fVec2* m_uvOffSet;
	fVec2* m_uvScale;
	fVec4* m_Color;

	inline constexpr fVec2 DefaultUVOffset() { return { 0.0f,0.0f }; }
	inline constexpr fVec2 DefaultUVScale() { return { 1.0f,1.0f }; }
	inline constexpr fVec4 DefaultColor() { return { 1.0f,1.0f,1.0f,1.0f }; }

	std::vector<std::shared_ptr<char[]>>	m_vtxShaderWriteDatas;
	std::vector<std::shared_ptr<char[]>>	m_pixelShaderWriteDatas;
};

#endif // !_____Render_HXX_____