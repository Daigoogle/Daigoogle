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