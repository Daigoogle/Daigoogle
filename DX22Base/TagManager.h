//	t@CผFTagManager.h
//	Tv		 F^OฬวมEว
//	์ฌา	 Fษกๅๅ
//	XVL^	 F2024/02/09	03:07	์ฌ	
//ธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถธถฒ

//	=-=-= CN[hK[h =-=-=
#ifndef _____TAG_MANAGER_H_____
#define _____TAG_MANAGER_H_____

//	=-=-= CN[h =-=-=
#include <vector>
#include <string>
#include "SingletonsMng.hxx"

/// @brief ^O๐วท้
/// @brief ฅฃฅฃฅฃ VOgลท ฅฃฅฃฅฃ
class TagManager :public Singleton<TagManager>
{
	friend class Singleton<TagManager>;
public:
	int AddTag(const std::string& tagName);
	int GetTagNo(const std::string& tagName);
	std::string GetTagName(int tagNo);

private:
	TagManager():Singleton(UPDATE_ORDER::NO_UPDATE) {}
	~TagManager();
	std::vector<std::string> m_tags;

};

#endif // !_____TAG_MANAGER_H_____