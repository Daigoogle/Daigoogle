//	ファイル名	：testScene.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/09/07 13:45:46
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____testScene_HXX_____
#define _____testScene_HXX_____

// =-=-= インクルード部 =-=-=
#include "SceneBase.hxx"

class testScene :public SceneBase
{
public:
	testScene();
	~testScene();

	bool Init() override;
private:

};

#endif // !_____testScene_HXX_____