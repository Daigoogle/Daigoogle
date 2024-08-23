#ifndef _____SPRITE_2D_TIP_H_____
#define _____SPRITE_2D_TIP_H_____

#include "transform.h"
#include "Texture.h"
#include <memory>
#include "Shader.h"
#include <string>
#include <vector>
#include "Component.h"

class Sprite2DComponent:public Component
{
public:
	Sprite2DComponent(void);
	void Init() override;
	void Update()override;
	void UnInit()override;

	void	LoadTexture(std::string);

	
	Transform* GetTransform(void)
	{
		return m_Transform;
	}

	Texture* GetTexture(void)
	{
		return m_texture;
	}

	void	SetColor(fVec4 color)
	{
		m_color = color;
	}

	fVec4	GetColor(void)
	{
		return m_color;
	}

	VertexShader* GetVertexShader(void)
	{
		return m_vertexShader.get();
	}

	PixelShader* GetPixelShader(void)
	{
		return m_pixelShader.get();
	}

	void	SetVertexShader(std::string);
	void	SetPixelShader(std::string);
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

	void	SetUVOffset(fVec2 offset)
	{
		m_uvOffSet = offset;
	}

	void	SetUVScale(fVec2 scale)
	{
		m_uvScale = scale;
	}

	fVec2	GetUVOffset(void)
	{
		return m_uvOffSet;
	}

	fVec2	GetUVScale(void)
	{
		return	m_uvScale;
	}

private:
	typedef struct
	{
		bool		bIsNewLoad;
		std::string	sPath;
	}tLoadData;

	Transform* m_Transform;
	Texture* m_texture;
	fVec4 m_color;
	fVec2 m_uvOffSet;
	fVec2 m_uvScale;
	std::unique_ptr<VertexShader>			m_vertexShader;
	std::unique_ptr<PixelShader>			m_pixelShader;
	std::vector<std::shared_ptr<char[]>>	m_vtxShaderWriteDatas;
	std::vector<std::shared_ptr<char[]>>	m_pixelShaderWriteDatas;
};

#endif // !_____SPRITE_2D_TIP_H_____