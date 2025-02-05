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

Object* Object::GetParent() const
{
	return m_pParent;
}

void Object::AddChild(Object* pChild)
{
	m_Children.push_back(pChild);
	pChild->m_pParent = this;
}

bool Object::IsActive() const
{
	return m_IsActive && (m_pParent ? m_pParent->IsActive() : true);
}

void Object::SetActive(bool IsActive)
{
	m_IsActive = IsActive;
}

const ID Object::GetID()
{
	return static_cast<ID>(m_ID);
}

void Object::UpdateChildren()
{
	if (!m_IsActive)
		return;
	Update();
	for(auto& elem:m_Children)
		elem->UpdateChildren();
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