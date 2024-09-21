//	�t�@�C����	�FModel.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/09/17 12:02:42
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Model_HXX_____
#define _____Model_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Render.hxx"
#include "ModelData.h"

class Model :public Render
{
public:
	Model();
	~Model();
	bool Init()override;

	void SetModel(const std::string& path);
protected:
	void Draw()override;

private:
	MODEL* m_Model;
};

#endif // !_____Model_HXX_____