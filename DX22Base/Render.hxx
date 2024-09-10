//	�t�@�C����	�FRender.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/11 20:42:52
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Render_HXX_____
#define _____Render_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Component.hxx"
#include "Shader.h"

class RenderMng;
class MeshBuffer;

/// @brief �`�敨�̊��N���X�B�P�̂ł̎g�p�s��
class Render :public Component
{
	friend class RenderMng;
public:
	Render();
	virtual ~Render();

	void SetTexture(const std::string& Path);
	void SetPixelShader(const std::string& Path);
	void SetVertexShader(const std::string& Path);

	void Update()override;
protected:
	virtual bool Init() = 0;
	virtual void Draw() = 0;


	void InitSetting();

	MeshBuffer* m_pMeshBuffer;
	Texture* m_pTexture;

	PixelShader* m_PixelShader;
	VertexShader* m_VertexShader;

	fVec2 m_uvOffSet;
	fVec2 m_uvScale;
	fVec4 m_Color;

	std::vector<std::shared_ptr<char[]>>	m_vtxShaderWriteDatas;
	std::vector<std::shared_ptr<char[]>>	m_pixelShaderWriteDatas;
};

#endif // !_____Render_HXX_____