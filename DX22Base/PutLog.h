#ifndef _____PUT_LOG_H_____
#define _____PUT_LOG_H_____

#include <Windows.h>
#include <string>

/// @brief �G���[���b�Z�[�W��MessageBox�ŏo��
/// @param �o�͕�����
void Error(LPCSTR);

/// @brief �o�̓E�B���h�E�ɒl��\������
/// @param �o�͕�����
void PutDebug(std::string);

#endif // !_____PUT_LOG_H_____