//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//	�t�@�C�����Feasing.h
//	�T�@�@�@�v�F�C�[�W���O
//	���@��@�ҁFItoDaigo
//
//	�������X�V����������
//	2023/12/08	ItoDaigo	�쐬
// 
//  ������  �T�v  ������
//	0.0f ~ 1.0f�Œl��n���ƁA����ɑΉ�����Easing�̒l��Ԃ��܂��B
// 
//	�ȉ��J�ڃO���t�Q�l��������
//	https://gizma.com/easing/
// 
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// ----------�C���N���[�h�K�[�h��----------
#ifndef _____EASING_H_____
#define _____EASING_H_____

namespace Easing
{
	float InSine(float num);
	float OutSine(float num);
	float InOutSine(float num);
	float InQuad(float num);
	float OutQuad(float num);
	float InOutQuad(float num);
	float InCubic(float num);
	float OutCubic(float num);
	float InOutCubic(float num);
	float InQuart(float num);
	float OutQuart(float num);
	float InOutQuart(float num);
	float InQuint(float num);
	float OutQuint(float num);
	float InOutQuint(float num);
	float InExpo(float num);
	float OutExpo(float num);
	float InOutExpo(float num);
	float InCirc(float num);
	float OutCirc(float num);
	float InOutCirc(float num);
	float InBack(float num);
	float OutBack(float num);
	float InOutBack(float num);
	float InElastic(float num);
	float OutElastic(float num);
	float InOutElastic(float num);
	float OutBounce(float num);
	float InBounce(float num);
	float InOutBounce(float num);
}; 

#endif // !_____EASING_H_____