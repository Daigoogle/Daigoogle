//	ファイル名	：ParsCmp.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/12/13 23:26:30
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____ParsCmp_HXX_____
#define _____ParsCmp_HXX_____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"

class ParsCmp : public Component
{
public:
	ParsCmp();
	~ParsCmp();
	
	bool Init()override;
	void Update()override;
	
private:
	Transform* m_Transform;
	fVec3 m_Direction;
};

#endif // !_____ParsCmp_HXX_____