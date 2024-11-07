#ifndef _____DDD_SDL_HXX_____
#define _____DDD_SDL_HXX_____

#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <forward_list>
#include <memory>

#include "Allocator.hxx"

namespace ddd {
	//template <typename Type, size_t Size>
	//	class array : public std::array<Type, Size, Allocator<Type>> {};

	template <typename Type>
		class vector : public std::vector<Type, Allocator<Type>> {};

	/// @brief Vector�̊g���N���X �\�[�g�⌟�����T�|�[�g���܂��B
	/// @brief ���A���P�[�^���T�|�[�g��
	/// @tparam Type �v�f�̌^
	template <typename Type>
	class ExVector : public std::vector<Type, Allocator<Type>> 
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

	template <typename Type>
		class priority_queue : public std::priority_queue<Type, Allocator<Type>> {};

	template <typename Type>
		class deque : public std::deque<Type, Allocator<Type>> {};

	//template <typename Key, typename Type>
		//class map : public std::map<Key, Type, Allocator<Type>> {};

	template <typename Key, typename Type>
		class multimap : public std::multimap<Key, Type, Allocator<Type>> {};

	template <typename Key, typename Type>
		class unordered_map : public std::unordered_map<Key, Type, Allocator<Type>> {};

	template <typename Key, typename Type>
		class unordered_multimap : public std::unordered_multimap<Key, Type, Allocator<Type>> {};

	template <typename Type>
		class set : public std::set<Type, Allocator<Type>> {};

	template <typename Type>
		class multiset : public std::multiset<Type, Allocator<Type>> {};

	template <typename Type>
		class unordered_set : public std::unordered_set<Type, Allocator<Type>> {};

	template <typename Type>
		class unordered_multiset : public std::unordered_multiset<Type, Allocator<Type>> {};

	template <typename Type>
		class list : public std::list<Type, Allocator<Type>> {};

	template <typename Type>
		class forward_list : public std::forward_list<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class shared_ptr : public std::shared_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class unique_ptr : public std::unique_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class weak_ptr : public std::weak_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class auto_ptr : public std::auto_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//Type* New(size_t size = 1)
	//{
	//	Allocator<Type> a;
	//	return a.allocate(size);
	//}

	//template <typename Type>
	//void Delete(Type* p , size_t size = 1)
	//{
	//	Allocator<Type> a;
	//	a.deallocate(p, size);
	//}
}

#endif // !_____DDD_SDL_HXX_____