//	�t�@�C����	�FWaveCubeCmp.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/12/13 22:02:11
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____WaveCubeCmp_HXX_____
#define _____WaveCubeCmp_HXX_____

// =-=-= �C���N���[�h�� =-=-=
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