//	�t�@�C����	�FLocation.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2025/01/06 13:53:24
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Location_HXX_____
#define _____Location_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "Vectors.hxx"

class Location
{
public:
	inline void SetLocation(const fVec3& location) { m_Location = location; }
	inline fVec3 GetLocation() { return m_Location; }
protected:
	fVec3 m_Location;// ���[�J�����W
};

#endif // !_____Location_HXX_____