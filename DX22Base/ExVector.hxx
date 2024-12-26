

#include <vector>
/// @brief Vectorの拡張クラス ソートや検索をサポートします。
/// @tparam Type 要素の型
template <typename Type>
class ExVector : public std::vector<Type> 
{
public:
	/// @brief 要素のソートを行います。
	/// @param IsUpper false(規定値):降順 / true:昇順
	void Sort(bool IsUpper = false)
	{
		if (!IsUpper) { // --- 降順 ---
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
		else { // --- 昇順 ---
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
	
	/// @brief 要素のソートを行います。
	/// @tparam Rtrn 比較する関数の戻り値の型
	/// @param func メンバ関数のポインタ
	/// @param IsUpper false(規定値):降順 / true:昇順
	template<typename Rtrn>
	void Sort(Rtrn(Type::* func)(),bool IsUpper = false)
	{
		if (!IsUpper) {// --- 降順 ---
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
		else {// --- 昇順 ---
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
	
	/// @brief 要素のソートを行います。
	/// @tparam mType 比較するメンバの型
	/// @param mVer 比較するメンバ変数のポインタ
	/// @param IsUpper false(規定値):降順 / true:昇順
	template<typename mType>
	void Sort(mType Type::*mVer,bool IsUpper = false)
	{
		if (!IsUpper) {// --- 降順 ---
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
		else {// --- 昇順 ---
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
	
	/// @brief 要素の検索を行います。
	/// @param search 検索したい値
	/// @return 要素番号を返します。見つからない場合は-1を返します。
	int Search(Type& search)
	{
		for(int i = 0;i < this->size();i++){
			if ((*this)[i] == search)
				return i;
		}
		return -1;
	}

	/// @brief 要素の検索を行います。
	/// @tparam sType 検索する値の型
	/// @param search 検索したい値
	/// @param sVer 比較するメンバ変数のポインタ
	/// @return 要素番号を返します。見つからない場合は-1を返します。
	template <typename sType>
	int Search(sType& search,sType Type::*sVer)
	{
		for (int i = 0; i < this->size(); i++) {
			if ((*this)[i].*sVer == search)
				return i;
		}
		return -1;
	}

	/// @brief 要素の検索を行います。
	/// @tparam sType 検索する値の型
	/// @param search 検索したい値
	/// @param sFunc 比較するメンバ関数のポインタ
	/// @return 要素番号を返します。見つからない場合は-1を返します。
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