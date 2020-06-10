#pragma once
#include <vector>
using std::vector;
#include "Texture.h"

//全局变量和函数

#ifdef __cplusplus
extern "C"
{
#endif


	//瓷砖的宽和高
	extern int		g_TileWidth;
	extern int		g_TileHeight;
	//地图的宽和高，以瓷砖个数为单位
	extern int		g_MapWidth;
	extern int		g_MapHeight;

	extern int		g_GridWidth;
	extern int		g_GridHeight;

	//地图图层外接包围矩形相对原点（左上角）偏移，以Tile宽和高为单位偏移
	extern int		g_offsetX;
	extern int		g_offsetY;
	//是否显示网格
	extern bool		g_bShowGrid;
	//地图是否可见
	extern bool		g_bVisible;
	

	//记录单元格原始尺寸
	extern int		g_OrgTileWidth;
	extern int		g_OrgTileHeight;

#define HALF_TILEWIDTH	g_TileWidth/2
#define HALF_TILEHEIGHT  g_TileHeight/2

#define HALF_GRIDWIDTH	g_GridWidth/2
#define HALF_GRIDHEIGHT  g_GridHeight/2

	//绘制
	void	DrawGrid(CDC* pDC);
	
	//返回地图包围矩形
	RECT	GetBoundRect();

	inline SIZE	GetTileSize(){	SIZE sz = { g_TileWidth,g_TileHeight}; return sz;	}
	//判断是否为空
	bool	IsEmpty();

	//屏幕坐标转换地图坐标
	inline POINT	ViewToMap(int x,int y)
	{
		x = x- g_offsetX;
		y=(y - g_MapWidth *g_TileHeight/2 -g_offsetY)*2;
		
		POINT pt;
		pt.x=(x-y)/g_TileWidth;
		pt.y=(x+y)/g_TileWidth;

		return pt;
	}
	
	//地图坐标转换屏幕坐标
	inline POINT	MapToView(INT x,INT y)
	{
		POINT pt;
		pt.x=(y+x)*g_TileWidth/2;
		pt.y=(g_MapWidth-1+y-x)*g_TileHeight/2;
		//加上偏移值
		pt.x += g_offsetX;
		pt.y += g_offsetY;
		return pt;
	}
	//屏幕坐标转换为单元格坐标
	inline POINT ViewToGrid(int x,int y)
	{
		x = x- g_offsetX;

		y = (y - g_MapWidth*(g_TileWidth/g_GridWidth) *HALF_GRIDHEIGHT - g_offsetY)*2;  

		POINT pt;
		pt.x=(x-y)/g_GridWidth;
		pt.y=(x+y)/g_GridWidth;

		return pt;
	}

	//地图坐标转换屏幕坐标
	inline POINT GridToView(int x,int y)
	{
		POINT pt;
		pt.x=(y+x)*HALF_GRIDWIDTH;
		pt.y=(g_MapWidth*(g_TileWidth/g_GridWidth)-1+y-x)*HALF_GRIDHEIGHT;
		//加上偏移值
		pt.x += g_offsetX;
		pt.y += g_offsetY;
		return pt;
	}


#ifdef __cplusplus
}
#endif
