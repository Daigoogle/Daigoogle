#ifndef _____FADE_H_____
#define _____FADE_H_____

#include "MeshBuffer.h"
#include "Shader.h"
#include "CameraBase.h"
#include "Transform.h"
#include "SingletonsMng.hxx"

/// @brief フェードを行い、管理する
class Fade final :public Singleton<Fade>
{
	friend class Singleton<Fade>;
public:
	bool Init();
	void Update();
	void Draw();

	void OutStart();
	void InStart();
	float GetAlpha();
	bool GetEnd();
private:
	Fade();
	~Fade();
	Transform* m_Transform;
	fVec4								m_color;
	fVec2								m_uvOffSet;
	fVec2								m_uvScale;
	Texture* m_texture;
	std::unique_ptr<VertexShader>			m_vertexShader;
	std::unique_ptr<PixelShader>			m_pixelShader;
	std::vector<std::shared_ptr<char[]>>	m_vtxShaderWriteDatas;
	std::vector<std::shared_ptr<char[]>>	m_pixelShaderWriteDatas;
	std::unique_ptr<MeshBuffer>		m_meshBuffer;

	float m_alpha;
	bool m_bIn : 1;
	bool m_bOut : 1;
	bool m_bEndFlg : 1;
};

#endif // !_____FADE_H_____