//	ファイル名：ScoreManager.h
//	概要		 ：スコアの管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/01/05	13:49	ItoDaigo	作成
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____SCORE_MANAGER_H_____
#define _____SCORE_MANAGER_H_____

#include "SingletonsMng.hxx"

/// @brief 値を保持し続ける
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class ScoreManager :public Singleton<ScoreManager>
{
	friend class Singleton<ScoreManager>;
public:
	bool Init();
	int increase();
	int GetScore();
private:
	ScoreManager() : Singleton(UPDATE_ORDER::NO_UPDATE), m_Score(0)
	{}
	~ScoreManager() {}
	int m_Score;

};

#endif // !_____SCORE_MANAGER_H_____