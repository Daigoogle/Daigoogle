// =-=-= インクルードガード部 =-=-=
#ifndef _____AUDIO_MANAGER_H_____
#define _____AUDIO_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include <string>
#include <vector>
#include <queue>
#include "Sound.h"
#include "SingletonsMng.hxx"
//#include "SoundEffectComponent.h"

class SoundEffectComponent;
class CameraBase;
class Transform;

/// @brief BGM,SEの管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class AudioManager :public Singleton<AudioManager>
{
	friend class Singleton<AudioManager>;
public:
	enum class BGM_KIND
	{
		BGM_TITLE,
		BGM_GAME,
		BGM_RESULT,
		BGM_MAX
	};

	enum class SE_KIND
	{
		SE_JUMP,
		SE_ENTER,
		SE_MAX
	};
	bool Init();
	void Update();

	void AddSoundEffect(SoundEffectComponent*);
	void PlayBGM(BGM_KIND kind);

	float GetVolume();
	void SetVolume(float volume);
	void IsStereo(bool);

private:	
	AudioManager();
	~AudioManager();

	void SetStereoVol(float);

	// BGM
	static const int BGM_FADEOUT_FRAME = 70;
	XAUDIO2_BUFFER* m_BGM_Buffer[static_cast<int>(BGM_KIND::BGM_MAX)];
	IXAudio2SourceVoice* m_BGM_Speaker;
	float m_fVolume;
	BGM_KIND m_BgmType;
	BGM_KIND m_BgmTypeOld;
	float m_fFadeOut;

	// SE
	static const int SE_SPEAKER_KIND = 10;		// 同時に流せるSEの最大数
	static const int ATTENUATION_DISTANCE = 50; // 音の減衰距離...(聞こえなくなる距離)
	XAUDIO2_BUFFER* m_SE_Buffer[static_cast<int>(SE_KIND::SE_MAX)];
	IXAudio2SourceVoice* m_SE_Speaker[SE_SPEAKER_KIND];
	Transform* m_SE_Tf[SE_SPEAKER_KIND];
	unsigned int m_SE_Speaker_Count;
	std::queue<SoundEffectComponent*> m_SoundEffects;
	CameraBase* m_Camera;
	bool m_IsStereo;
	DWORD dwChannelMask;
	float outputMatrix[8];
	IXAudio2MasteringVoice* m_Mastering;
};

#endif // !_____AUDIO_MANAGER_H_____