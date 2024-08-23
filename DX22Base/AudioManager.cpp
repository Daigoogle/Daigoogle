#include "AudioManager.h"
#include "SoundEffectComponent.h"
#include "CameraManager.h"
#include "Transform.h"
#include <x3daudio.h>

const float rad = 180 / 3.141592f;

static const char* BGM_FilePath[static_cast<int>(AudioManager::BGM_KIND::BGM_MAX)] =
{
	"Title",
	"Game",
	"Result"
};

static const char* SE_FilePath[static_cast<int>(AudioManager::SE_KIND::SE_MAX)] = 
{
	"Jump",
	"Enter",
};

AudioManager::AudioManager()
	: Singleton(UPDATE_ORDER::LAST_UPDATE)
	, m_BgmType(BGM_KIND::BGM_MAX)
	, m_BgmTypeOld(BGM_KIND::BGM_MAX)
	, m_fVolume(0.0f)
	, m_fFadeOut(1.0f)
	, m_SE_Speaker_Count(0)
	, m_Camera(nullptr)
	, m_IsStereo(false)
{
	for (int i = 0; i < 8; i++)
		outputMatrix[i] = 0;
	

}

AudioManager::~AudioManager()
{
	if (m_BgmType != BGM_KIND::BGM_MAX)
		m_BGM_Speaker->Stop();
	m_BGM_Speaker->DestroyVoice();

	for (unsigned i = 0; i < m_SE_Speaker_Count && i < SE_SPEAKER_KIND; i++)
	{
		m_SE_Speaker[i]->Stop();
		m_SE_Speaker[i]->DestroyVoice();
	}

	UninitSound();

	//delete m_BGM_Buffer;
	//delete[] m_SE_Buffer;
}

bool AudioManager::Init()
{
	InitSound();
	std::string folderPath = "Assets/Music/";

	//各BGMのロード
	for (int i = 0; i < static_cast<int>(BGM_KIND::BGM_MAX); i++)
	{
		m_BGM_Buffer[i] = LoadSound((folderPath + "BGM/" + BGM_FilePath[i] + ".wav").c_str(), true);
	}

	//各SEのロード
	for (int i = 0; i < static_cast<int>(SE_KIND::SE_MAX); i++)
	{
		m_SE_Buffer[i] = LoadSound((folderPath + "SE/" + SE_FilePath[i] + ".wav").c_str(), false);
	}

	m_Mastering = GetMastering();
	m_Mastering->GetChannelMask(&dwChannelMask);
	return true;
}

void AudioManager::Update()
{
	//	BGMの更新
	if (m_BgmType != m_BgmTypeOld)
	{	// BGMの更新＆上書き
		if (m_fFadeOut <= 0.0f)
		{
			m_fFadeOut = 1.0f;
			if (m_BgmTypeOld != BGM_KIND::BGM_MAX)
			{	// 初回じゃないなら
				m_BGM_Speaker->Stop();
				m_BGM_Speaker->DestroyVoice();
			}
			m_BGM_Speaker = PlaySound(m_BGM_Buffer[static_cast<int>(m_BgmType)]);
			if (m_BGM_Speaker != nullptr)
				m_BGM_Speaker->SetVolume(m_fVolume * m_fFadeOut);
			m_BgmTypeOld = m_BgmType;
		}
		else
		{
			m_fFadeOut -= 0.01f;
			if (m_BgmTypeOld != BGM_KIND::BGM_MAX)
				m_BGM_Speaker->SetVolume(m_fVolume * m_fFadeOut);
		}
	}

	//	SEの更新
	while (!m_SoundEffects.empty())
	{
		SoundEffectComponent* Comp = m_SoundEffects.front();
		m_SoundEffects.pop();
		auto se_kind = Comp->GetSEKind();
		m_SE_Tf[m_SE_Speaker_Count % SE_SPEAKER_KIND] = Comp->GetTransform();
		if (m_SE_Speaker_Count >= SE_SPEAKER_KIND)
		{
			m_SE_Speaker[m_SE_Speaker_Count % SE_SPEAKER_KIND]->Stop();
			m_SE_Speaker[m_SE_Speaker_Count % SE_SPEAKER_KIND]->DestroyVoice();
		}
		m_SE_Speaker[m_SE_Speaker_Count % SE_SPEAKER_KIND] = PlaySound(m_SE_Buffer[static_cast<int>(se_kind)]);
		if( m_SE_Speaker[m_SE_Speaker_Count % SE_SPEAKER_KIND] != nullptr)
			m_SE_Speaker[m_SE_Speaker_Count % SE_SPEAKER_KIND]->SetVolume(m_fVolume * 5);
		Comp->PlaySE(SE_KIND::SE_MAX);
		m_SE_Speaker_Count++;
	}

	if (m_IsStereo)
	{
		//	カメラの更新
		m_Camera = Singleton<CameraManager>::GetInstance().GetMainCamera();
		DirectX::XMFLOAT3 loPos = m_Camera->GetLook();
		fVec2 normPos = { loPos.x,loPos.z };
		DirectX::XMFLOAT3 capos = m_Camera->GetPos();
		fVec2 camPos = { capos.x,capos.z };
		for (unsigned i = 0; i < m_SE_Speaker_Count && i < SE_SPEAKER_KIND; i++)
		{	// ステレオ適応
			fVec3 sepos = m_SE_Tf[i]->GetWorldPosition();
			fVec2 sePos = { sepos.x,sepos.z };
			fVec2 ans1 = normPos - camPos;
			fVec2 ans2 = sePos - camPos;
			float rot = atan2f(ans1.y, ans1.x) - atan2f(ans2.y, ans2.x);
			float ansA = rot / 3.14f;
			XAUDIO2_VOICE_DETAILS VoiceDetails;
			m_SE_Speaker[i]->GetVoiceDetails(&VoiceDetails);
			XAUDIO2_VOICE_DETAILS MasVoiceDetails;
			m_Mastering->GetVoiceDetails(&MasVoiceDetails);
			SetStereoVol(ansA);
			m_SE_Speaker[i]->SetOutputMatrix(NULL, VoiceDetails.InputChannels, MasVoiceDetails.InputChannels, outputMatrix);
		}
	}
}

void AudioManager::AddSoundEffect(SoundEffectComponent* comp)
{
	m_SoundEffects.push(comp);
}

void AudioManager::PlayBGM(BGM_KIND kind)
{
	m_BgmType = kind;
}

float AudioManager::GetVolume()
{
	return m_fVolume;
}

void AudioManager::SetVolume(float volume)
{
	m_fVolume = volume;
}

void AudioManager::IsStereo(bool isstereo)
{
	m_IsStereo = isstereo;
}

/// @brief outputMatrixを設定する
/// @param pan ...右か左か、
/// -1(左) ～ 1(右)
void AudioManager::SetStereoVol(float pan)
{
	float left = 0.5f - pan / 2;
	float right = 0.5f + pan / 2;

	switch (dwChannelMask)
	{
	case SPEAKER_MONO:
		outputMatrix[0] = 1.0;
		break;
	case SPEAKER_STEREO:
	case SPEAKER_2POINT1:
	case SPEAKER_SURROUND:
		outputMatrix[0] = left;
		outputMatrix[1] = right;
		break;
	case SPEAKER_QUAD:
		outputMatrix[0] = outputMatrix[2] = left;
		outputMatrix[1] = outputMatrix[3] = right;
		break;
	case SPEAKER_4POINT1:
		outputMatrix[0] = outputMatrix[3] = left;
		outputMatrix[1] = outputMatrix[4] = right;
		break;
	case SPEAKER_5POINT1:
	case SPEAKER_7POINT1:
	case SPEAKER_5POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = left;
		outputMatrix[1] = outputMatrix[5] = right;
		break;
	case SPEAKER_7POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = outputMatrix[6] = left;
		outputMatrix[1] = outputMatrix[5] = outputMatrix[7] = right;
		break;
	}
}