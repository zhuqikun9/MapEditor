#pragma once
#include "texture.h"


class CCurSelImage :
	public CTexture
{
public:
	CCurSelImage(void);
	~CCurSelImage(void);

	//自适应绘制整个图片
	void	Draw(CDC* pDC,int xDest,int yDest,int nDestWidth,int nDestHeight);

};

