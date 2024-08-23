//	ファイル名：ModelRegister.h
//	概要		 ：モデルの読み込み、格納
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/02/08	18:13	作成	
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

//	=-=-= インクルードガード部 =-=-=
#ifndef _____MODEL_REGISTER_H_____
#define _____MODEL_REGISTER_H_____

//	=-=-= インクルード部 =-=-=
#include <map>
#include <string>
#include "Model.h"
#include "SingletonsMng.hxx"

/// @brief モデルの管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class ModelRegister final :public Singleton<ModelRegister>
{
	friend Singleton<ModelRegister>;
public:
	Model* LoadModel(const std::string& Path);

private:
	ModelRegister();
	~ModelRegister();

	std::map<std::string, Model*> m_Models;
};

#endif // !_____MODEL_REGISTER_H_____