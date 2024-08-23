#include "TextureRegister.h"
#include "PutLog.h"

TextureRegister::TextureRegister()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

TextureRegister::~TextureRegister()
{
	for (auto& Value:m_Textures)
	{
		delete Value.second;
	}
}

Texture* TextureRegister::LoadTexture(const std::string& path)
{
	if (m_Textures.count(path))
		return m_Textures[path];
	m_Textures[path] = new Texture;
	if (m_Textures[path]->Create(path.c_str()) != S_OK)
		Error(path.c_str());
	return m_Textures[path];
}