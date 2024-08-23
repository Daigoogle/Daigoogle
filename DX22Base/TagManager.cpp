#include "TagManager.h"

TagManager::~TagManager()
{
	m_tags.clear();
}

int TagManager::AddTag(const std::string& tagName)
{
	for (int i = 0; i < m_tags.size(); i++)
		if (m_tags[i] == tagName)
			return i;
	m_tags.push_back(tagName);
	return m_tags.size() - 1;
}

int TagManager::GetTagNo(const std::string& tagName)
{
	for (int i = 0; i < m_tags.size(); i++)
		if (m_tags[i] == tagName)
			return i;
	return -1;
}

std::string TagManager::GetTagName(int tagNo)
{
	return m_tags[tagNo];
}