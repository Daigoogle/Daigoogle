#include "Allocator.hxx"
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <sstream>

//#include "Defines.hxx"
#include "ddd_sdl.hxx"

namespace {
	/// @brief 型毎のデータ管理・ソート用
	struct putt {
		size_t GetSize() { return size; }
		std::string type = {};
		size_t size = 0;
	};

	/// @brief ポインタ毎の情報を記録する構造体
	struct ReakCheck {
		size_t size;// メモリサイズ
		unsigned short TypeTag;// 型のタグ
		unsigned short FileTag;// ファイルのタグ
		unsigned short Line;// 行数
	};

	/// @brief ポインタ毎の情報を記録するマップのポインタ
	/// @brief クラスで直に定義すると、処理順の関係でデストラクタ時にエラーが出るためポインタで持つ。
	std::map<void*, ReakCheck>* ReakMap;

	/// @brief メモリリークやデータ量などの情報を管理するクラス
	struct ___reak 
	{ 
		___reak() { ReakMap = &ReakMapOlg; }
		~___reak() 
		{
			std::cout << "--------------------- リーク一覧 ------------------------" << std::endl;
			for (auto& elem : ReakMapOlg)
			{
				std::cout << TypeNames[elem.second.TypeTag] << "::" <<
					elem.second.size << "byte at File:" <<
					FileNames[elem.second.FileTag] << " To Line:" <<
					elem.second.Line << std::endl;
			}
			rewind(stdin); (void)getchar();
			ReakMap = nullptr;
		}
		size_t usingMemorySize = 0; // 使用中のメモリ総量
		std::map <std::string, size_t > memMap; // 型毎メモリ使用量の格納先
		std::vector<std::string> FileNames = { "UnKnown" }; // ファイル名の格納先
		std::vector<std::string> TypeNames = { "UnKnown" }; // 型名の格納先
		std::map<void*, ReakCheck> ReakMapOlg; // ポインタ毎の情報を格納するマップ
	};

	/// @brief メモリリーク・データ管理構造体のインスタンス
	/// @brief メモリ管理クラスをグローバルで持つことにより、デストラクタでリーク情報を表示する。
	___reak reak;
	
}

/// @brief メモリリークの情報を整理して返す
/// @param size データサイズ
/// @param type データ型
/// @param FileName ファイル名
/// @param Line 行数
/// @return ポインタに関連づける情報
ReakCheck MakeReakCheckParam(size_t size, const type_info& type, const std::string& FileName, int Line)
{
	reak.usingMemorySize += size;
	ReakCheck c;

	std::istringstream sst(FileName);
	std::string file;
	// ファイルパスからファイル名だけを取得
	while (std::getline(sst, file, '\\'));

	addMemorySize(type.name(), size);
	reak.memMap[type.name()] += size;

	c.size = size;
	c.Line = Line;

	/// 検索して無ければ追加
	bool sucsess = false;
	for (size_t i = 0; i < reak.FileNames.size(); i++) {
		if (reak.FileNames[i] == file) {
			c.FileTag = i;
			sucsess = true;
			break;
		}
	}
	if (!sucsess) {
		c.FileTag = reak.FileNames.size();
		reak.FileNames.push_back(file);
	}

	sucsess = false;

	file = type.name();

	/// 検索して無ければ追加
	for (size_t i = 0; i < reak.TypeNames.size(); i++) {
		if (reak.TypeNames[i] == file) {
			c.TypeTag = i;
			sucsess = true;
			break;
		}
	}
	if (!sucsess) {
		c.TypeTag = reak.TypeNames.size();
		reak.TypeNames.push_back(file);
	}

	return c;
}

void* operator new(size_t size, const type_info& type,const std::string& FileName, int Line)
{	
	void* p = malloc(size);
	(*ReakMap)[p] = MakeReakCheckParam(size,type,FileName,Line);
	return p;
}
void* operator new[](size_t size, const type_info& type, const std::string& FileName, int Line)
{
	void* p = malloc(size);
	(*ReakMap)[p] = MakeReakCheckParam(size, type, FileName, Line);
	return p;
}


void* operator new(size_t size)
{
	reak.usingMemorySize += size;
	return malloc(size);
}
void* operator new[](size_t size)
{
	reak.usingMemorySize += size;
	return malloc(size);
}
//void operator delete(void* p) noexcept
//{
//	if (ReakMap && ReakMap->contains(p))
//		ReakMap->erase(p);
//	free(p);
//}
void operator delete(void* p, size_t size) noexcept
{
	reak.usingMemorySize -= size;
	if(ReakMap && ReakMap->contains(p))
		ReakMap->erase(p);
	free(p);
}

/// @brief メモリ管理のための関数　型毎のデータ量を記録します。
/// @param type 型名
/// @param size Byte数
void addMemorySize(const std::string& type,size_t size)
{
	reak.memMap[type] += size;
	reak.usingMemorySize += size;
}

/// @brief メモリ管理のための関数　型毎のデータ量を記録します。
/// @param type 型名
/// @param size Byte数
void deleteMemorySize(const std::string& type, size_t size)
{
	reak.memMap[type] -= size;
	reak.usingMemorySize -= size;
}

/// @brief 型毎のメモリ使用量を表示します。
void ShowUsingMemorySize()
{	
	// ベクター配列に格納
	ddd::ExVector<putt> v;
	for (auto& elem : reak.memMap)
		v.push_back({ elem.first, elem.second });

	v.Sort(&putt::GetSize);

	// 表示
	std::cout << std::endl << "メモリ使用量：" << reak.usingMemorySize << std::endl << "内訳{" << std::endl;
	for (auto& elem : v) 
	{
		if(elem.size)
			std::cout << "  " << elem.type << std::endl << "    ┗ 割合：" <<(100 * elem.size) / (float)reak.usingMemorySize << "％  小計 :" << std::setw(4) << elem.size << "byte" << std::endl;
	}
	std::cout << "};" << std::endl;
}