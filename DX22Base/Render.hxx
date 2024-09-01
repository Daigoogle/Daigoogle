//	�t�@�C����	�FRender.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/11 20:42:52
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Render_HXX_____
#define _____Render_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Component.hxx"

class RenderMgr;

/// @brief �`�敨�̊��N���X�B�P�̂ł̎g�p�s��
class Render :public Component
{
	friend class RenderMgr;
public:
	Render();
	virtual ~Render();

protected:
	virtual bool Init() = 0;
	void Update()override final;
	virtual void Draw() = 0;
	uint32 m_MeshID;
};

#endif // !_____Render_HXX_____