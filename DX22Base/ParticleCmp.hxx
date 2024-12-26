//	�t�@�C����	�FParticleCmp.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/12/13 22:43:38
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____ParticleCmp_HXX_____
#define _____ParticleCmp_HXX_____

// =-=-= �C���N���[�h�� =-=-=
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