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

enum class Ease
{
	InSine,
	OutSine,
	InOutSine,
	InQuad,
	OutQuad,
	InOutQuad,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuart,
	OutQuart,
	InOutQuart,
	InQuint,
	OutQuint,
	InOutQuint,
	InExpo,
	OutExpo,
	InOutExpo,
	InCirc,
	OutCirc,
	InOutCirc,
	InBack,
	OutBack,
	InOutBack,
	InElastic,
	OutElastic,
	InOutElastic,
	OutBounce,
	InBounce,
	InOutBounce
};

namespace eas
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

/// @brief �C�[�W���O���s���֐�
/// @tparam Type �C�[�W���O���������^�B - ���Z�q���I�[�o�[���[�h�ςȂ�\���̂���
/// @param alpha 0~1�̃C�[�W���O��l��n��
/// @param Start �C�[�W���O�̊J�n�l
/// @param End �C�[�W���O�̏I���l
/// @param EaseType �C�[�W���O�̎��
/// @return �C�[�W���O���ꂽ�l
template<typename Type>
Type Easing(float alpha, Type Start, Type End, Ease EaseType)
{
	Type result = End - Start;

	switch (EaseType)
	{
	case Ease::InSine:			alpha = eas::InSine(alpha);			break;
	case Ease::OutSine:			alpha = eas::OutSine(alpha);		break;
	case Ease::InOutSine:		alpha = eas::InOutSine(alpha);		break;
	case Ease::InQuad:			alpha = eas::InQuad(alpha);			break;
	case Ease::OutQuad:			alpha = eas::OutQuad(alpha);		break;
	case Ease::InOutQuad:		alpha = eas::InOutQuad(alpha);		break;
	case Ease::InCubic:			alpha = eas::InCubic(alpha);		break;
	case Ease::OutCubic:		alpha = eas::OutCubic(alpha);		break;
	case Ease::InOutCubic:		alpha = eas::InOutCubic(alpha);		break;
	case Ease::InQuart:			alpha = eas::InQuart(alpha);		break;
	case Ease::OutQuart:		alpha = eas::OutQuart(alpha);		break;
	case Ease::InOutQuart:		alpha = eas::InOutQuart(alpha);		break;
	case Ease::InQuint:			alpha = eas::InQuint(alpha);		break;
	case Ease::OutQuint:		alpha = eas::OutQuint(alpha);		break;
	case Ease::InOutQuint:		alpha = eas::InOutQuint(alpha);		break;
	case Ease::InExpo:			alpha = eas::InExpo(alpha);			break;
	case Ease::OutExpo:			alpha = eas::OutExpo(alpha);		break;
	case Ease::InOutExpo:		alpha = eas::InOutExpo(alpha);		break;
	case Ease::InCirc:			alpha = eas::InCirc(alpha);			break;
	case Ease::OutCirc:			alpha = eas::OutCirc(alpha);		break;
	case Ease::InOutCirc:		alpha = eas::InOutCirc(alpha);		break;
	case Ease::InBack:			alpha = eas::InBack(alpha);			break;
	case Ease::OutBack:			alpha = eas::OutBack(alpha);		break;
	case Ease::InOutBack:		alpha = eas::InOutBack(alpha);		break;
	case Ease::InElastic:		alpha = eas::InElastic(alpha);		break;
	case Ease::OutElastic:		alpha = eas::OutElastic(alpha);		break;
	case Ease::InOutElastic:	alpha = eas::InOutElastic(alpha);	break;
	case Ease::OutBounce:		alpha = eas::OutBounce(alpha);		break;
	case Ease::InBounce:		alpha = eas::InBounce(alpha);		break;
	case Ease::InOutBounce:		alpha = eas::InOutBounce(alpha);	break;
	default:break;
	}

	return result * alpha + Start;
}

#endif // !_____EASING_H_____