//	�t�@�C����	�FAnyUpdateComp.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/09/15 17:52:35
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____AnyUpdateComp_HXX_____
#define _____AnyUpdateComp_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Component.hxx"
#include <functional>

class AnyUpdateComp : public Component
{
public:
	AnyUpdateComp();
	~AnyUpdateComp();
	
	bool Init()override;
	void Update()override;

	void SetFunc(std::function<void()> func);
private:
	std::function<void()> m_Func;
};

#endif // !_____AnyUpdateComp_HXX_____