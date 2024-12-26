//	ファイル名	：WaveCubeCmp.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/12/13 22:02:11
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____WaveCubeCmp_HXX_____
#define _____WaveCubeCmp_HXX_____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"


class WaveCubeCmp : public Component
{
public:
	WaveCubeCmp();
	~WaveCubeCmp();
	
	bool Init()override;
	void Update()override;
	
private:
	float m_Time;
	Transform* m_Transform;
};

#endif // !_____WaveCubeCmp_HXX_____