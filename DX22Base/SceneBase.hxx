//	�t�@�C����	�FClass.hxx
//	�@�T�@�v�@	�F
//	��@���@��	�F 
//	 �쐬����	�F
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Class_HXX_____
#define _____Class_HXX_____

// =-=-= �C���N���[�h�� =-=-=

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