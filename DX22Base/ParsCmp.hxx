//	�t�@�C����	�FParsCmp.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/12/13 23:26:30
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____ParsCmp_HXX_____
#define _____ParsCmp_HXX_____

// =-=-= �C���N���[�h�� =-=-=
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