#include "StdAfx.h"
#include "TileLayer.h"
#include "MapEditor.h"

void CTile::Draw(CDC* pDC)
{ 
	if(m_ResID==-1)
		return;
	POINT pt = MapToView(m_PosX,m_PosY);
	theApp.m_ResMgr.GetTile(m_ResID).Draw(pDC,pt.x,pt.y,g_TileWidth,g_TileHeight);
}


CTileLayer::CTileLayer()
{
	m_bVisible = true;
}
CTileLayer::~CTileLayer()
{
	Destroy();
}
void CTileLayer::Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight)
{
	Destroy();

	m_TileSet.resize(g_MapWidth*g_MapHeight);

}


//在屏幕上（x,y）处贴瓷砖，参数为图片的编号，
void CTileLayer::AddTile(int ResID,int x,int y)
{
	if(ResID==-1)
		return;
	POINT  pt;
	//将屏幕坐标转换为地图坐标
	pt = ViewToMap(x,y);
	//判断越界
	if(pt.x>=0&&pt.x<g_MapWidth&&pt.y>=0&&pt.y<g_MapHeight)	
	{
		m_TileSet.at(pt.x+pt.y*g_MapWidth).SetResID(ResID);
		m_TileSet.at(pt.x+pt.y*g_MapWidth).SetPos(pt.x,pt.y);
	}		
}
//删除屏幕上（x,y）处瓷砖
void CTileLayer::DelTile(int x,int y)
{
	POINT  pt;
	pt = ViewToMap(x,y);
	if(pt.x>=0&&pt.x<g_MapWidth&&pt.y>=0&&pt.y<g_MapHeight)	
		m_TileSet.at(pt.x+pt.y*g_MapWidth).SetEmpty();//置空
}

void CTileLayer::Draw(CDC* pDC)
{
	if(!m_bVisible)
		return;
	//画图层,	本地图原点坐标为(0,g_MapWidth*g_TileHeight/2)

	for(int y=0;y<g_MapHeight;y++)
		for(int x=g_MapWidth-1;x>=0;x--)
		{	
			m_TileSet.at(x+y*g_MapWidth).Draw(pDC);
		}

}

