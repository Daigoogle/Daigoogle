//	ファイル名	：Model.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/09/17 12:02:42
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Model_HXX_____
#define _____Model_HXX_____

// =-=-= インクルード部 =-=-=
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