#ifndef _____SCENE_COMPONENT_TEST_H_____
#define _____SCENE_COMPONENT_TEST_H_____

#include "SceneBase.h"

class SoundEffectComponent;

class SceneComponentTest :
    public SceneBase
{
public:
    SceneComponentTest();
    ~SceneComponentTest();

    void Init()override;
    void Update()override;
    void UnInit()override;

private:
    SoundEffectComponent* m_Se;
};

#endif // !_____SCENE_COMPONENT_TEST_H_____