#include "GameObjectMng.hxx"
#include "GameObjectInst.hxx"
#include "GameObject.hxx"
#include "SceneMng.hxx"
#include "SceneBase.hxx"

GameObjectMng::GameObjectMng()
	: Singleton(UPDATE_ORDER::THIRD_UPDATE)
{

}

GameObjectMng::~GameObjectMng()
{

}

bool GameObjectMng::Init()
{
	return true;
}

void GameObjectMng::Update()
{
	InitObjects();// �܂��͏�����
	DeleteObject();// �s�v���̍폜
	UpdateObjects(SceneMng::GetInstance().GetNowScene());// �X�V
}

void GameObjectMng::InitObjects()
{
	// �L���[�̒��g��S�ď�����
	for (auto& elem: m_ObjectsLoadQueue){
		while (elem.second.empty()){
			 elem.second.front()->Init();
			 m_ObjectsQueue[elem.first].push_back(std::move(elem.second.front()));// Init����Update�Ɉړ�
			 elem.second.pop();
		}
	}
}

void GameObjectMng::UpdateObjects(SceneBase* pScene)
{
	if (!pScene)return;
	// �V�[���L���[�̒��g���X�V
	//while (m_ObjectsQueue[pScene].empty())
	//	m_ObjectsQueue[pScene].front()->Update();
	for (auto& elem:m_ObjectsQueue[pScene]){
		elem->Update();
		if (elem->m_IsDelete) {
			m_ObjectsDeleteQueue[elem->m_ObjectID] = elem->m_pScene;
		}
	}
}

void GameObjectMng::DeleteSceneObjects(SceneBase* pScene)
{
	m_ObjectsQueue[pScene].clear();
}

GameObject GameObjectMng::MakeObject(SceneBase* pScene)
{
	GameObjectInst* pInst = new GameObjectInst;// �C���X�^���X�̐���
	pInst->m_pScene = pScene;		// �V�[���̐ݒ�
	GameObject obj;					// �I�u�W�F�N�g�̐���
	obj.SetInstance(pInst);	// �C���X�^���X��ݒ�
	m_ObjectsLoadQueue[pScene].push(pInst);// �L���[�ɒǉ�
	return obj;
}

/// @brief �I�u�W�F�N�g�̍폜
void GameObjectMng::DeleteObject()
{
	std::unordered_map<SceneBase*,int> bisection;// �����ɏ������邽�߁A�ȑO�̒T���͈͂��L��
	for (auto& elem : m_ObjectsDeleteQueue) {
		uint32_t id = elem.first;
		SceneBase* pScene = elem.second;
		int Right = (int)m_ObjectsQueue[pScene].size() - 1; // �T���͈͂̉E�[
		int& mid = bisection[pScene]; // �O��̒T���l���擾
		int Left = mid;	// �T���͈͂̍��[
		mid = static_cast<int>( (Right - mid) * 0.5f + mid); // �����l�̏�����

		// �񕪒T��
		while (true) {	
			if (m_ObjectsQueue[pScene][mid]->m_ObjectID < id) {
				Left = mid;
				mid = static_cast<int>((Right + Left) * 0.5f);
			}
			else if (m_ObjectsQueue[pScene][mid]->m_ObjectID > id) {
				Right = mid;
				mid = static_cast<int>((Right + Left) * 0.5f);
			}
			else {
				m_ObjectsQueue[pScene].erase(m_ObjectsQueue[pScene].begin() + mid);
				break;
			}
			if (Right - 1 == Left) {
				if(m_ObjectsQueue[pScene][Right]->m_ObjectID == id)
					m_ObjectsQueue[pScene].erase(m_ObjectsQueue[pScene].begin() + Right);
				else if(m_ObjectsQueue[pScene][Left]->m_ObjectID == id)
					m_ObjectsQueue[pScene].erase(m_ObjectsQueue[pScene].begin() + Left);
				break;
			}
		}
	}
	m_ObjectsDeleteQueue.clear();
}