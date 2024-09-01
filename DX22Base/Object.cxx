#include "Object.hxx"

#include "GameObject.hxx"

Object::Object()
	: m_pParent(nullptr)
	, m_Children()
	, m_IsActive(true)
{
}

Object::~Object()
{
	m_Children.clear();
}

void Object::UpdateChildren()
{
	if (!m_IsActive)
		return;
	this->Update();
	for(auto& elem:m_Children)
		elem->UpdateChildren();
}

GameObject Object::MakeObject()
{
	return GameObjectMng::GetInstance().MakeObject(this);
}

void Object::Delete()
{

	while (!m_Children.empty()) {
		m_Children.front()->Delete();
		m_Children.pop_front();
	}


}

/// @brief Ø‚è—£‚µˆ—B•K‚¸íœ‚âˆÙ“®‚Æˆê‚Ég‚¤‚±‚Æ
/// @param pChild 
void Object::RemoveChild(Object* pChild)
{
	for (int i = 0; i < m_Children.size();i++) {
		if (m_Children[i] == pChild) {
			m_Children.erase(m_Children.begin() + i);
			break;
		}
	}
}