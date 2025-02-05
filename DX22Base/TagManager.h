//	�t�@�C�����FTagManager.h
//	�T�v		 �F�^�O�̒ǉ��E�Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/09	03:07	�쐬	
//������������������������������������������������������������������������������������������������������

//	=-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____TAG_MANAGER_H_____
#define _____TAG_MANAGER_H_____

//	=-=-= �C���N���[�h�� =-=-=
#include <vector>
#include <string>
#include "SingletonsMng.hxx"

/// @brief �^�O���Ǘ�����
/// @brief ������������ �V���O���g���ł� ������������
class TagManager :public Singleton<TagManager>
{
	friend class Singleton<TagManager>;
public:
	Tag AddTag(const std::string& tagName);
	Tag GetTagNo(const std::string& tagName);
	std::string GetTagName(Tag tagNo);

private:
	TagManager():Singleton(UPDATE_ORDER::NO_UPDATE) {}
	~TagManager();
	std::vector<std::string> m_tags;

};

#endif // !_____TAG_MANAGER_H_____