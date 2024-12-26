//	ファイル名	：ParticleCmp.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/12/13 22:43:38
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____ParticleCmp_HXX_____
#define _____ParticleCmp_HXX_____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"
#include <vector>

class ParticleCmp : public Component
{
public:
	ParticleCmp();
	~ParticleCmp();
	
	bool Init()override;
	void Update()override;
	
private:
	float m_Time;
	SceneBase* m_Scene;
	std::vector<Transform*> m_Particles;
	size_t m_cnt;
};

#endif // !_____ParticleCmp_HXX_____