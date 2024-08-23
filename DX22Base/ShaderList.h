//	ファイル名：ShaderList.h
//	概要		 ：シェーダーの読み込み、格納
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/08	18:58	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

//	=-=-= インクルードガード部 =-=-=
#ifndef _____SHADER_LIST_H_____
#define _____SHADER_LIST_H_____

//	=-=-= インクルード部 =-=-=
#include <map>
#include <string>
#include "Shader.h"
#include "SingletonsMng.hxx"

/// @brief シェーダーの管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class ShaderList final :public Singleton<ShaderList>
{
	friend Singleton<ShaderList>;
public:
	PixelShader* LoadPixelShader(const std::string& path);
	VertexShader* LoadVertexShader(const std::string& path);

private:
	ShaderList();
	~ShaderList();

	std::map<std::string, PixelShader*>		m_PixelShaders;
	std::map<std::string, VertexShader*>	m_VertexShaders;
};

#endif // !_____SHADER_LIST_H_____