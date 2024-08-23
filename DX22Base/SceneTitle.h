#ifndef _____SCENE_TITLE_H_____
#define _____SCENE_TITLE_H_____

#include "SceneBase.h"
#include "Sprite2DComponent.h"
#include "CameraBase.h"
#include "Transform.h"

class SoundEffectComponent;

class SceneTitle :
    public SceneBase
{
public: 
    SceneTitle();
    ~SceneTitle();
    void Init()override;
    void Update()override;
    void UnInit()override;
private:
    Sprite2DComponent* m_Sprite;
    Sprite2DComponent* m_SprObj;
    Transform* m_tfBack;
    Transform* m_tfFront;
    CameraBase* m_Camera;
    SoundEffectComponent* m_SE;
};

#endif