#include "StdAfx.h"
#include "Layer.h"
#include "MapEditor.h"



//全局变量
int		g_MapWidth = 0;
int		g_MapHeight =0;
int		g_TileWidth =0;
int		g_TileHeight =0;

int		g_GridWidth = 32;
int		g_GridHeight = 16;

int		g_OrgTileWidth = 0;
int		g_OrgTileHeight = 0;
int		g_offsetX = 0;
int		g_offsetY = 0;
//默认显示网格
bool	g_bShowGrid = false;
//默认地图可见
bool	g_bVisible = true;



//绘制
void DrawGrid(CDC* pDC)
{
	
	if(g_bShowGrid)
	{ //绘制网格
		CPoint pt;
		CPen pen(PS_DOT ,1,RGB(216,216,216));
		CPen* pOldPen = pDC->SelectObject(&pen);
		for(int x=0;x<g_MapWidth+1;x++)
		{
			pt = MapToView(x,0);
			pDC->MoveTo(pt.x,pt.y+g_TileHeight/2);
			pt = MapToView(x,g_MapHeight);
			pDC->LineTo(pt.x,pt.y+g_TileHeight/2);
		}
		for(int y=0;y<g_MapHeight+1;y++)
		{
			pt = MapToView(0,y);
			pDC->MoveTo(pt.x,pt.y+g_TileHeight/2);
			pt = MapToView(g_MapWidth,y);
			pDC->LineTo(pt.x,pt.y+g_TileHeight/2);
		}
	
		pen.DeleteObject();
		pDC->SelectObject(pOldPen);
			
	}
}


RECT GetBoundRect()
{ 
	RECT rect;
	rect.left = 0 +g_offsetX ;
	rect.top = 0 +g_offsetY;
	rect.right = rect.left+ (g_MapWidth + g_MapHeight)*g_TileWidth/2 + g_offsetX;
	rect.bottom = rect.top+ (g_MapWidth + g_MapHeight)*g_TileHeight/2 + g_offsetY;
	return rect;
}


bool	IsEmpty()
{ 
	if(!g_MapWidth||!g_MapHeight) 
		return true; 
	return false;
}