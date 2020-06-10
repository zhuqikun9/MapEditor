#include "StdAfx.h"
#include "BlockLayer.h"
#include "MapEditor.h"

CBlockLayer* CBlockLayer::s_BlockLayer= NULL;


CBlockLayer::CBlockLayer(void)
{
	if(!s_BlockLayer)
		s_BlockLayer = this;

	m_bVisible = true;
}


CBlockLayer::~CBlockLayer(void)
{
	Destroy();
}
void CBlockLayer::Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight)
{
	Destroy();

	m_Width = g_MapWidth*(g_TileWidth/g_GridWidth);
	m_Height = g_MapHeight*(g_TileHeight/g_GridHeight);
	m_bBlockArray.resize(m_Width*m_Height);
	//初始化全部可通过
	for(int x=0;x<m_Width;x++)
		for(int y=0;y<m_Height;y++)
		{
			m_bBlockArray[x+y*m_Width] = true;
		}
}
void CBlockLayer::Draw(CDC* pDC)
{
	if(!m_bVisible)
		return;
	for(int x=0;x<m_Width;x++)
		for(int y=0;y<m_Height;y++)
		{	//绘制障碍物标记，碰撞块
			if(!m_bBlockArray.at(x+y*m_Width))
				theApp.m_ResMgr.m_BlockImage.Draw(pDC,GridToView(x,y).x,GridToView(x,y).y,g_GridWidth,g_GridHeight);
		}

}

