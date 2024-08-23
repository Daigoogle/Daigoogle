//	�t�@�C�����FTextureRegister.h
//	�T�v		 �F�e�N�X�`���̓ǂݍ��݁A�i�[
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/18	14:59	�쐬	
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____TEXTURE_REGISTER_H_____
#define _____TEXTURE_REGISTER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "Texture.h"
#include <map>
#include <string>
#include "SingletonsMng.hxx"

/// @brief �e�N�X�`���̊Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
class TextureRegister final :public Singleton<TextureRegister>
{
	friend Singleton<TextureRegister>;
public:
	Texture* LoadTexture(const std::string& path);

private:
	TextureRegister();
	~TextureRegister();

	std::map<std::string, Texture*> m_Textures;
};

#endif // !_____TEXTURE_REGISTER_H_____