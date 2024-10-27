#ifndef _____DEFINES_HXX_____
#define _____DEFINES_HXX_____

/// @brief std::vector,std::deque��ΏۂƂ����\�[�g�����ł��B
/// @param container �\�[�g�Ώۂ̃R���e�i
/// @param order �~���F< /�����F>
/// @param menber �\�[�g�Ώۂ̃����o�[ ���h�b�g���Z�q��A���[���Z�q���܂ߋL�q���Ă��������B
#define SORT_STL(container,order,menber) \
for(int i = 0;i < (int) container .size() - 1;i++)\
{\
	for(int j = i + 1;j < (int) container .size();j++)\
	{\
		if( container [i] menber order container [j] menber )\
		{\
			auto temp = container [i];\
			container [i] = container [j];\
			container [j] = temp;\
		}\
	}\
}

#endif // !_____DEFINES_HXX_____