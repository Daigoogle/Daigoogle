#include "ShaderList.h"

ShaderList::ShaderList()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
{
}

ShaderList::~ShaderList()
{
	for (auto& elem :m_PixelShaders)
		delete elem.second;
	for (auto& elem : m_VertexShaders)
		delete elem.second;
}

PixelShader* ShaderList::LoadPixelShader(const std::string& path)
{
	if (m_PixelShaders.count(path))
		return m_PixelShaders[path];
	m_PixelShaders[path] = new PixelShader();
	if (m_PixelShaders[path]->Load(path.c_str()) != S_OK)
		MessageBox(NULL, path.c_str(), "PixelShader Load Error", MB_OK);
	return m_PixelShaders[path];
}

VertexShader* ShaderList::LoadVertexShader(const std::string& path)
{
	if (m_VertexShaders.count(path))
		return m_VertexShaders[path];
	m_VertexShaders[path] = new VertexShader();
	if (m_VertexShaders[path]->Load(path.c_str()) != S_OK)
		MessageBox(NULL, path.c_str(), "VertexShader Load Error", MB_OK);
	return m_VertexShaders[path];
}