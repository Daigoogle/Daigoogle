//	ファイル名	：Class.hxx
//	　概　要　	：
//	作　成　者	： 
//	 作成日時	：
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Class_HXX_____
#define _____Class_HXX_____

// =-=-= インクルード部 =-=-=
#include "Object.hxx"
#include "SceneMng.hxx"

class GameObject;

class SceneBase:public Object
{
	friend class SceneMng;
public:
	

private:
	virtual bool Init() = 0;
	virtual void Update() {};

	SceneBase() {}
	virtual ~SceneBase();
};

#endif // !_____Class_HXX_____