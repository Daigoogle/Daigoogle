#include "GameObject.hxx"
#include "DebugRestriction.hxx"

#include "Component.hxx"

GameObject::GameObject()
	: m_Components()
	, m_Name()
	, m_Tag(0)
{

}


GameObject::~GameObject()
{

}

void GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

const std::string& GameObject::GetName()
{
	return m_Name;
}

unsigned GameObject::GetTag()
{
	return m_Tag;	
}

void GameObject::SetTag(unsigned tag)
{
	m_Tag = tag;
}

Transform* GameObject::GetTransform()
{
	return this;
}

bool GameObject::Init(){
	for (auto& elem : m_Components) {
		elem.get()->Init();
	}
	return true;
}
void GameObject::Update(){
	for (auto& elem : m_Components) {
		elem.get()->Update();
	}
}