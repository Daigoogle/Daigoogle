#ifndef _____CUBE_TIP_H_____
#define _____CUBE_TIP_H_____

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Transform.h"
#include "Vectors.hxx"
#include "Component.h"
#include <memory>

class CubeComponent:public Component
{
public:
	CubeComponent();
	
	void Init()override;
	void Update()override;
	void UnInit()override;	
	
	void LoadTexture(std::string);

	Transform* GetTransform();

	Texture* GetTexture()
	{
		return m_Texture;
	}

	void SetColor(fVec4 color)
	{
		m_Color = color;
	}

	fVec4 GetColor()
	{
		return m_Color;
	}

	VertexShader* GetVertexShader()
	{
		return m_Vs;
	}

	PixelShader* GetPixelShader()
	{
		return m_Ps;
	}

	void SetVertexShader(std::string);
	void SetPixelShader(std::string);
	void	RegisterDataVertexShader(int, int);
	void	WriteDataVertexShader(int, void*, int);
	void	RegisterDataPixelShader(int, int);
	void	WriteDataPixelShader(int, void*, int);

	std::vector<std::shared_ptr<char[]>>& GetVertexShaderWriteData(void)
	{
		return m_vtxShaderWriteDatas;
	}

	std::vector<std::shared_ptr<char[]>>& GetPixelShaderWriteData(void)
	{
		return m_pixelShaderWriteDatas;
	}

	void SetUVOffset(fVec2 offset)
	{
		m_uvOffSet = offset;
	}

	void SetUVScale(fVec2 scale)
	{
		m_uvScale = scale;
	}

	fVec2 GetUVOffset(void)
	{
		return m_uvOffSet;
	}

	fVec2 GetUVScale(void)
	{
		return	m_uvScale;
	}

private:
	Transform* m_Transform;
	fVec2 m_uvOffSet;
	fVec2 m_uvScale;
	MeshBuffer* m_Mesh;
	VertexShader* m_Vs;
	PixelShader* m_Ps;
	Texture* m_Texture;
	fVec4 m_Color;
	std::vector<std::shared_ptr<char[]>>	m_vtxShaderWriteDatas;
	std::vector<std::shared_ptr<char[]>>	m_pixelShaderWriteDatas;
};

#endif // !_____CUBE_TIP_H_____