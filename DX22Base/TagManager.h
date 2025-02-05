//	ファイル名：TagManager.h
//	概要		 ：タグの追加・管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/09	03:07	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

//	=-=-= インクルードガード部 =-=-=
#ifndef _____TAG_MANAGER_H_____
#define _____TAG_MANAGER_H_____

//	=-=-= インクルード部 =-=-=
#include <vector>
#include <string>
#include "SingletonsMng.hxx"

/// @brief タグを管理する
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class TagManager :public Singleton<TagManager>
{
	friend class Singleton<TagManager>;
public:
	Tag AddTag(const std::string& tagName);
	Tag GetTagNo(const std::string& tagName);
	std::string GetTagName(Tag tagNo);

private:
	TagManager():Singleton(UPDATE_ORDER::NO_UPDATE) {}
	~TagManager();
	std::vector<std::string> m_tags;

};

#endif // !_____TAG_MANAGER_H_____