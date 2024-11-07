

#include <vector>
/// @brief Vector�̊g���N���X �\�[�g�⌟�����T�|�[�g���܂��B
/// @tparam Type �v�f�̌^
template <typename Type>
class ExVector : public std::vector<Type> 
{
public:
	/// @brief �v�f�̃\�[�g���s���܂��B
	/// @param IsUpper false(�K��l):�~�� / true:����
	void Sort(bool IsUpper = false)
	{
		if (!IsUpper) { // --- �~�� ---
			for (int i = 0; i < this->size() - 1; i++){
				for (int j = i + 1; j < this->size(); j++){
					if ((*this)[i] < (*this)[j]){
						auto temp = (*this)[i];
						(*this)[i] = (*this)[j];
						(*this)[j] = temp;
					}
				}
			}
		}
		else { // --- ���� ---
			for (int i = 0; i < this->size() - 1; i++) {
				for (int j = i + 1; j < this->size(); j++) {
					if ((*this)[i] > (*this)[j]) {
						auto temp = (*this)[i];
						(*this)[i] = (*this)[j];
						(*this)[j] = temp;
					}
				}
			}
		}
	}
	
	/// @brief �v�f�̃\�[�g���s���܂��B
	/// @tparam Rtrn ��r����֐��̖߂�l�̌^
	/// @param func �����o�֐��̃|�C���^
	/// @param IsUpper false(�K��l):�~�� / true:����
	template<typename Rtrn>
	void Sort(Rtrn(Type::* func)(),bool IsUpper = false)
	{
		if (!IsUpper) {// --- �~�� ---
			for (int i = 0; i < this->size() - 1; i++) {
				for (int j = i + 1; j < this->size(); j++) {
					if (((*this)[i].*func)() < ((*this)[j].*func)()) {
						auto temp = (*this)[i];
						(*this)[i] = (*this)[j];
						(*this)[j] = temp;
					}
				}
			}
		}
		else {// --- ���� ---
			for (int i = 0; i < this->size() - 1; i++) {
				for (int j = i + 1; j < this->size(); j++) {
					if (((*this)[i].*func)() > ((*this)[j].*func)()) {
						auto temp = (*this)[i];
						(*this)[i] = (*this)[j];
						(*this)[j] = temp;
					}
				}
			}
		}
	}
	
	/// @brief �v�f�̃\�[�g���s���܂��B
	/// @tparam mType ��r���郁���o�̌^
	/// @param mVer ��r���郁���o�ϐ��̃|�C���^
	/// @param IsUpper false(�K��l):�~�� / true:����
	template<typename mType>
	void Sort(mType Type::*mVer,bool IsUpper = false)
	{
		if (!IsUpper) {// --- �~�� ---
			for (int i = 0; i < this->size() - 1; i++) {
				for (int j = i + 1; j < this->size(); j++) {
					if ((*this)[i].*mVer < (*this)[j].*mVer) {
						auto temp = (*this)[i];
						(*this)[i] = (*this)[j];
						(*this)[j] = temp;
					}
				}
			}
		}
		else {// --- ���� ---
			for (int i = 0; i < this->size() - 1; i++) {
				for (int j = i + 1; j < this->size(); j++) {
					if ((*this)[i].*mVer > (*this)[j].*mVer) {
						auto temp = (*this)[i];
						(*this)[i] = (*this)[j];
						(*this)[j] = temp;
					}
				}
			}
		}
	}
	
	/// @brief �v�f�̌������s���܂��B
	/// @param search �����������l
	/// @return �v�f�ԍ���Ԃ��܂��B������Ȃ��ꍇ��-1��Ԃ��܂��B
	int Search(Type& search)
	{
		for(int i = 0;i < this->size();i++){
			if ((*this)[i] == search)
				return i;
		}
		return -1;
	}

	/// @brief �v�f�̌������s���܂��B
	/// @tparam sType ��������l�̌^
	/// @param search �����������l
	/// @param sVer ��r���郁���o�ϐ��̃|�C���^
	/// @return �v�f�ԍ���Ԃ��܂��B������Ȃ��ꍇ��-1��Ԃ��܂��B
	template <typename sType>
	int Search(sType& search,sType Type::*sVer)
	{
		for (int i = 0; i < this->size(); i++) {
			if ((*this)[i].*sVer == search)
				return i;
		}
		return -1;
	}

	/// @brief �v�f�̌������s���܂��B
	/// @tparam sType ��������l�̌^
	/// @param search �����������l
	/// @param sFunc ��r���郁���o�֐��̃|�C���^
	/// @return �v�f�ԍ���Ԃ��܂��B������Ȃ��ꍇ��-1��Ԃ��܂��B
	template <typename sType>
	int Search(sType& search, sType (Type::*sFunc)())
	{
		for (int i = 0; i < this->size(); i++) {
			if (((*this)[i].*sFunc)() == search)
				return i;
		}
		return -1;
	}
};