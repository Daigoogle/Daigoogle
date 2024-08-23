#include "Sprite3DComponent.h"
#include "Sprite3DManager.h"
#include "TextureRegister.h"
#include "BaseObject.h"
#include "PutLog.h"
#include "ShaderList.h"

Sprite3DComponent::Sprite3DComponent()
	: m_Transform(nullptr)
	, m_Color{1.0f,1.0f,1.0f,1.0f}
	, m_uvOffSet{0.0f,0.0f}
	, m_uvScale{1.0f,1.0f}
	, m_Ps(nullptr)
	, m_Vs(nullptr)
{
	//m_Transform.reset(new Transform);
}

Sprite3DComponent::~Sprite3DComponent()
{

}

void Sprite3DComponent::Init()
{
	// ---------デフォルトシェーダのロード----------
	if (m_Ps == nullptr)
		m_Ps = Singleton<ShaderList>::GetInstance().LoadPixelShader("Assets/Shader/Sprite3D_Defalt_PS.cso");
	if (m_Vs == nullptr)
		m_Vs = Singleton<ShaderList>::GetInstance().LoadVertexShader("Assets/Shader/Sprite3D_Defalt_VS.cso");

	// ---------デフォルトテクスチャのロード----------
	if(!m_Textures.count(0))
		m_Textures[0] = Singleton<TextureRegister>::GetInstance().LoadTexture("Assets/Texture/defalt.png");

	// ---------- トランスフォームを取得 ----------
	m_Transform = GetBaseObject().GetComponent<Transform>();
	if (m_Transform == nullptr)
		Error("Not Component : Transform\n to Sprite3DTip");
}

void Sprite3DComponent::Update()
{
	//// ---------テクスチャのロード----------
	//if (m_textureLoadData.bIsNewLoad)
	//{
	//	;	//テクスチャをロード
	//}
	//// ---------頂点シェーダのロード----------
	//if (m_vtxShaderLoadData.bIsNewLoad)
	//{
	//	HRESULT hr = m_Vs->Load(m_vtxShaderLoadData.sPath.c_str());//ロード
	//	if (FAILED(hr))
	//	{
	//		int a = 10;
	//	}
	//}
	//// ---------ピクセルシェーダのロード----------
	//if (m_pixelShaderLoadData.bIsNewLoad)
	//{
	//	m_pixelShader->Load(m_pixelShaderLoadData.sPath.c_str());	//ロード
	//}

	// ---------マネージャに登録----------
	Sprite3DManager& manager = Singleton<Sprite3DManager>::GetInstance();
	manager.AddQueue(this);
}

void Sprite3DComponent::UnInit()
{

}

Transform* Sprite3DComponent::GetTransform()
{
	if(m_Transform == nullptr)
		m_Transform = GetBaseObject().GetComponent<Transform>();
	return m_Transform;
}

std::map<UINT,Texture*> Sprite3DComponent::GetTexture()
{
	return m_Textures;
}

void Sprite3DComponent::SetColor(fVec4 color)
{
	m_Color = color;
}

fVec4 Sprite3DComponent::GetColor()
{
	return m_Color;
}

VertexShader* Sprite3DComponent::GetVertexShader()
{
	return m_Vs;
}

PixelShader* Sprite3DComponent::GetPixelShader()
{
	return m_Ps;
}

void Sprite3DComponent::LoadTexture(UINT slot,std::string sPath)
{
	m_Textures[slot] = Singleton<TextureRegister>::GetInstance().LoadTexture(sPath);
	//m_Texture->Create(sPath.c_str());
}
void Sprite3DComponent::LoadTexture(std::string sPath)
{
	m_Textures[0] = Singleton<TextureRegister>::GetInstance().LoadTexture(sPath);
	//m_Texture->Create(sPath.c_str());
}

void Sprite3DComponent::SetVertexShader(std::string sPath)
{
	m_Vs = Singleton<ShaderList>::GetInstance().LoadVertexShader(sPath);
}

void Sprite3DComponent::SetPixelShader(std::string sPath)
{
	m_Ps = Singleton<ShaderList>::GetInstance().LoadPixelShader(sPath);
}

void Sprite3DComponent::RegisterDataVertexShader(int nIndex, int nByte)
{
	// ----------データの領域を作成----------
	while (m_vtxShaderWriteDatas.size() < nIndex + 1)
	{
		std::shared_ptr<char[]>	byteData(new char[nByte]);
		m_vtxShaderWriteDatas.push_back(std::move(byteData));
	}
}

void Sprite3DComponent::RegisterDataPixelShader(int nIndex, int nByte)
{
	// ----------データの領域を作成----------
	while (m_pixelShaderWriteDatas.size() < nIndex + 1)
	{
		std::shared_ptr<char[]> byteData(new char[nByte]);
		m_pixelShaderWriteDatas.push_back(std::move(byteData));
	}
}

void Sprite3DComponent::WriteDataVertexShader(int nIndex, void* pData, int nByte)
{
	// ----------データの書き込み----------
	void* pDest = reinterpret_cast<void*>(m_vtxShaderWriteDatas[nIndex].get());
	memcpy(pDest, pData, nByte);
}

void Sprite3DComponent::WriteDataPixelShader(int nIndex, void* pData, int nByte)
{
	// ----------データの書き込み----------
	void* pDest = reinterpret_cast<void*>(m_pixelShaderWriteDatas[nIndex].get());
	memcpy(pDest, pData, nByte);
	float* a;
	a = (float*)pDest;
	int b = 0;
}

std::vector<std::shared_ptr<char[]>>& Sprite3DComponent::GetVertexShaderWriteData(void)
{
	return m_vtxShaderWriteDatas;
}

std::vector<std::shared_ptr<char[]>>& Sprite3DComponent::GetPixelShaderWriteData(void)
{
	return m_pixelShaderWriteDatas;
}

void Sprite3DComponent::SetUVOffset(fVec2 offset)
{
	m_uvOffSet = offset;
}

void Sprite3DComponent::SetUVScale(fVec2 scale)
{
	m_uvScale = scale;
}

fVec2 Sprite3DComponent::GetUVOffset(void)
{
	return m_uvOffSet;
}

fVec2 Sprite3DComponent::GetUVScale(void)
{
	return	m_uvScale;
}