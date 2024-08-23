// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SOUND_EFFECT_COMPONENT_H_____
#define _____SOUND_EFFECT_COMPONENT_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "Component.h"
#include "Transform.h"
#include "AudioManager.h"

/// @brief ���ʉ���炷
/// @brief �R���|�[�l���g
class SoundEffectComponent :
    public Component
{
public:
    SoundEffectComponent();
    ~SoundEffectComponent();

    void Init()override;
    void Update()override;
    void UnInit()override;

    void PlaySE(AudioManager::SE_KIND);
    Transform* GetTransform();
    AudioManager::SE_KIND GetSEKind();

private:
    AudioManager::SE_KIND m_SE_Start;
    Transform* m_pTransform;
};

#endif // !_____SOUND_EFFECT_COMPONENT_H_____