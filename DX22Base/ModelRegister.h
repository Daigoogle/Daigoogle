//	�t�@�C�����FModelRegister.h
//	�T�v		 �F���f���̓ǂݍ��݁A�i�[
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/08	18:13	�쐬	
//������������������������������������������������������������������������������������������������������

//	=-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____MODEL_REGISTER_H_____
#define _____MODEL_REGISTER_H_____

//	=-=-= �C���N���[�h�� =-=-=
#include <map>
#include <string>
#include "Model.h"
#include "SingletonsMng.hxx"

/// @brief ���f���̊Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
class ModelRegister final :public Singleton<ModelRegister>
{
	friend Singleton<ModelRegister>;
public:
	Model* LoadModel(const std::string& Path);

private:
	ModelRegister();
	~ModelRegister();

	std::map<std::string, Model*> m_Models;
};

#endif // !_____MODEL_REGISTER_H_____