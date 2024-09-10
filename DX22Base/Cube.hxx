//	ファイル名	：Cube.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/08/28 22:02:36
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Cube_HXX_____
#define _____Cube_HXX_____

// =-=-= インクルード部 =-=-=
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