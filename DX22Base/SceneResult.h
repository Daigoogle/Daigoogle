#ifndef _____SCENE_RESULT_H_____
#define _____SCENE_RESULT_H_____

#include "SceneBase.h"
#include "CameraBase.h"

class NumSprite2D;
class Sprite2DComponent;
class SoundEffectComponent;

class SceneResult :
    public SceneBase
{
public:
    SceneResult();
    ~SceneResult();
    void Init()override;
    void Update()override;
    void UnInit()override;
private:
    CameraBase* m_Camera;

    NumSprite2D* m_Score;
    Sprite2DComponent* m_Haikei;
    bool m_PressSpacerr;
    int m_nFCntrr;
    SoundEffectComponent* m_SE;
};

#endif // !_____SCENE_RESULT_H_____