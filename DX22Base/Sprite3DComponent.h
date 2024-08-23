#ifndef _____SPRITE_3D_COMPONENT_H_____
#define _____SPRITE_3D_COMPONENT_H_____

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Transform.h"
#include "Vectors.hxx"
#include <memory>
#include "Component.h"
#include <map>

class Sprite3DComponent:public Component
{
public:
	Sprite3DComponent();
	~Sprite3DComponent();

	void Init()override;
	void Update()override;
	void UnInit()override;
	
	void LoadTexture(UINT slot,std::string);
	void LoadTexture(std::string);
	Transform* GetTransform();
	std::map<UINT,Texture*> GetTexture();
	void SetColor(fVec4 color);
	fVec4 GetColor();
	VertexShader* GetVertexShader();
	PixelShader* GetPixelShader();

	void SetVertexShader(std::string);
	void SetPixelShader(std::string);
	void	RegisterDataVertexShader(int, int);
	void	WriteDataVertexShader(int, void*, int);
	void	RegisterDataPixelShader(int, int);
	void	WriteDataPixelShader(int, void*, int);

	std::vector<std::shared_ptr<char[]>>& GetVertexShaderWriteData(void);
	std::vector<std::shared_ptr<char[]>>& GetPixelShaderWriteData(void);
	void SetUVOffset(fVec2 offset);
	void SetUVScale(fVec2 scale);
	fVec2 GetUVOffset(void);
	fVec2 GetUVScale(void);

private:
	Transform* m_Transform;
	fVec2 m_uvOffSet;
	fVec2 m_uvScale;
	MeshBuffer* m_Mesh;
	PixelShader* m_Ps;
	VertexShader* m_Vs;
	std::map<UINT,Texture*> m_Textures;
	fVec4 m_Color;
	std::vector<std::shared_ptr<char[]>>	m_vtxShaderWriteDatas;
	std::vector<std::shared_ptr<char[]>>	m_pixelShaderWriteDatas;
private:
	static DirectX::XMFLOAT4X4 m_WVP[3];
};

#endif // !_____SPRITE_3D_COMPONENT_H_____