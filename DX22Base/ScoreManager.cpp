#include "ScoreManager.h"

bool ScoreManager::Init()
{
	m_Score = 0;
	return true;
}
int ScoreManager::increase()
{
	m_Score++;
	return m_Score;
}
int  ScoreManager::GetScore()
{
	return m_Score;
}