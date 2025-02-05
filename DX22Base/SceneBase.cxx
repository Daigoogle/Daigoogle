#include "SceneBase.hxx"

#include "GameObject.hxx"
#include "SceneMng.hxx"

SceneBase::SceneBase()
	: m_LoadComplete(false)
	, m_SceneComponent()
{

}

SceneBase::~SceneBase()
{

}

// ���[�h�����i����O��j
void SceneBase::Loading(SceneBase** ppInstantChange)
{
	// ����������
	FalseCheck(this->Init());

	// ���[�h�����t���O�𗧂Ă�
	m_LoadComplete = true;

	// ���̃N���X�����`�F���W�Ȃ�`�F���W������
	if (this == *ppInstantChange)
		SceneManager::GetInstance().ChangeScene(this);
}

void SceneBase::ReadFile(const std::string& path)
{
	// �t�@�C���ǂݍ��݁E�I�u�W�F�N�g����
}