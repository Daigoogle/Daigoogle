
// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SCENE_INIT_H_____
#define _____SCENE_INIT_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "SceneBase.h"
#include "Sprite2DComponent.h"

/// @brief �Q�[���N������̂݁B���S�Ƃ�
class SceneInit :
    public SceneBase
{
public:
    SceneInit();
    ~SceneInit();

    void Init()override;
    void Update()override;
    void UnInit()override;

private:
    Sprite2DComponent* m_TeamRogo;
    Sprite2DComponent* m_EnginRogo;
    Sprite2DComponent* m_FromRogo;
    int m_FrameCount;
};

#endif // !_____SCENE_INIT_H_____