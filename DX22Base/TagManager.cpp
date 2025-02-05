#include "TagManager.h"

TagManager::~TagManager()
{
	m_tags.clear();
}

Tag TagManager::AddTag(const std::string& tagName)
{
	for (int i = 0; i < m_tags.size(); i++)
		if (m_tags[i] == tagName)
			return i + 1;
	m_tags.push_back(tagName);
	return (int)m_tags.size();
}

Tag TagManager::GetTagNo(const std::string& tagName)
{
	for (int i = 0; i < m_tags.size(); i++)
		if (m_tags[i] == tagName)
			return i + 1;
	return 0;
}

std::string TagManager::GetTagName(Tag tagNo)
{
	return m_tags[tagNo - 1];
}