//	ファイル名	：AnyUpdateComp.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/09/15 17:52:35
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____AnyUpdateComp_HXX_____
#define _____AnyUpdateComp_HXX_____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"
#include <functional>

class AnyUpdateComp : public Component
{
public:
	AnyUpdateComp();
	~AnyUpdateComp();
	
	bool Init()override;
	void Update()override;

	void SetFunc(std::function<void()> func);
private:
	std::function<void()> m_Func;
};

#endif // !_____AnyUpdateComp_HXX_____