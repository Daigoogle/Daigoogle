#ifndef _____DEFINES_HXX_____
#define _____DEFINES_HXX_____

/// @brief std::vector,std::dequeを対象としたソート処理です。
/// @param container ソート対象のコンテナ
/// @param order 降順：< /昇順：>
/// @param menber ソート対象のメンバー ※ドット演算子やアロー演算子も含め記述してください。
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