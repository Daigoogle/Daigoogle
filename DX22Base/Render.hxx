//	�t�@�C����	�FRender.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/11 20:42:52
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Render_HXX_____
#define _____Render_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "RenderMgr.hxx"

class Render
{
	friend class RenderMgr;
public:
	Render();
	virtual ~Render();

	void Draw();
protected:
};

#endif // !_____Render_HXX_____