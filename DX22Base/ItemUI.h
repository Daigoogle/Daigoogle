#ifndef ___ITEMUI_H___
#define ___ITEMUI_H___

#include "Texture.h"

class ItemUI 
{
public:
	ItemUI();
	~ItemUI();
	void Draw();

private:
	Texture* m_pTexture;


};


#endif // !___ITEMUI_H___

