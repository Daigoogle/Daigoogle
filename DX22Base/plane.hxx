//	�t�@�C����	�Fplane.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/08/28 22:04:50
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____plane_HXX_____
#define _____plane_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Render.hxx"

class plane :public Render
{
public:
	plane();
	~plane();

	void Draw()override;
protected:
	bool Init()override;
private:
	bool m_IsBillboard;
	
};

#endif // !_____plane_HXX_____