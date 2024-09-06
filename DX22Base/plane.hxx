//	ファイル名	：plane.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/08/28 22:04:50
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____plane_HXX_____
#define _____plane_HXX_____

// =-=-= インクルード部 =-=-=
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