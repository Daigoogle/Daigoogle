//	�t�@�C����	�FClass.hxx
//	�@�T�@�v�@	�F
//	��@���@��	�F 
//	 �쐬����	�F
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Class_HXX_____
#define _____Class_HXX_____

// =-=-= �C���N���[�h�� =-=-=
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