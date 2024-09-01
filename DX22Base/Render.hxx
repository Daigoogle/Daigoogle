//	ファイル名	：Render.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/11 20:42:52
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Render_HXX_____
#define _____Render_HXX_____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"

class RenderMgr;

/// @brief 描画物の基底クラス。単体での使用不可
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