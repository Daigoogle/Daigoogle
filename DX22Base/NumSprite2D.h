#ifndef _____NUM_SPRITE_3D_H_____
#define _____NUM_SPRITE_3D_H_____

//#define _HAS_STD_BYTE 0

#include "BaseObject.h"
#include "SceneBase.h"
#include "Component.h"
#include "Sprite2DComponent.h"

class NumSprite2D:public Component
{
public:
	NumSprite2D();
	~NumSprite2D();

	void Init()override;
	void Update()override;
	void UnInit()override;

	void SetScene(SceneBase*);
	void SetNum(unsigned int);
	void SetColor(fVec4);

private:
	BaseObject* m_num;
	Sprite2DComponent** m_Sprite;
	SceneBase* m_Scene;
	int m_Digit;
	fVec4 m_Color;
};

#endif // !_____NUM_SPRITE_3D_H_____