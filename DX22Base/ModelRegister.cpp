#include "ModelRegister.h"
#include "PutLog.h"

ModelRegister::ModelRegister()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
{

}

ModelRegister::~ModelRegister()
{
	for (auto& elem : m_Models)
		delete elem.second;
}

Model* ModelRegister::LoadModel(const std::string& path)
{
	if (m_Models.count(path))
		return m_Models[path];
	m_Models[path] = new Model();
	if (m_Models[path]->Load(path.c_str(), 1.0f, Model::XFlip) == false)
		Error(path.c_str());
	return m_Models[path];
}