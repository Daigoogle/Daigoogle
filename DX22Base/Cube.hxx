//	�t�@�C����	�FCube.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/08/28 22:02:36
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Cube_HXX_____
#define _____Cube_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Render.hxx"

class Cube :public Render, public Component
{
public:
	Cube();
	~Cube();
	void Draw()override;
protected:
	bool Init()override;
private:

};

#endif // !_____Cube_HXX_____