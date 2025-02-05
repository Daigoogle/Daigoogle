//	ファイル名	：Location.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/01/06 13:53:24
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Location_HXX_____
#define _____Location_HXX_____

// =-=-= インクルード部 =-=-=
#include "Vectors.hxx"

class Location
{
public:
	inline void SetLocation(const fVec3& location) { m_Location = location; }
	inline fVec3 GetLocation() { return m_Location; }
protected:
	fVec3 m_Location;// ローカル座標
};

#endif // !_____Location_HXX_____