//	ファイル名：TextureRegister.h
//	概要		 ：テクスチャの読み込み、格納
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/18	14:59	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____TEXTURE_REGISTER_H_____
#define _____TEXTURE_REGISTER_H_____

// =-=-= インクルード部 =-=-=
#include "Texture.h"
#include <map>
#include <string>
#include "SingletonsMng.hxx"

/// @brief テクスチャの管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class TextureRegister final :public Singleton<TextureRegister>
{
	friend Singleton<TextureRegister>;
public:
	Texture* LoadTexture(const std::string& path);

private:
	TextureRegister();
	~TextureRegister();

	std::map<std::string, Texture*> m_Textures;
};

#endif // !_____TEXTURE_REGISTER_H_____