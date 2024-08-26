//	ファイル名	：Class.hxx
//	　概　要　	：
//	作　成　者	： 
//	 作成日時	：
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Class_HXX_____
#define _____Class_HXX_____

// =-=-= インクルード部 =-=-=

class GameObject;

class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase();

	virtual bool Init() = 0;
	virtual void Update() {};

	GameObject MakeObject();

private:

};

#endif // !_____Class_HXX_____