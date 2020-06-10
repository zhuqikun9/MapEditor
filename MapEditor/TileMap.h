#pragma once
#include "Layer.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "BlockLayer.h"
#include "EventLayer.h"


struct MAPHEADER
{
	int MapWidth;
	int MapHeight;
	int TileWidth;
	int TileHeight;
	int SceneObjCount;
	int MonsterCount;
};

class CTileMap 
	
{
public:
	CTileMap(void);
	virtual ~CTileMap(void);

	//创建
	void	Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight);
	//更新
	void	Update(float fElapsedTime);
	//绘制
	void	Draw(CDC* pDC);
	//加载地图数据
	bool	LoadMapData(LPCTSTR filename);
	//将地图数据存入.map文件中
	bool	SaveMapData(LPCTSTR filename);

	CTileLayer&	GetTileLayer(){	return m_TileLayer; }
	CObjectLayer&	GetObjectLayer(){ return m_ObjectLayer; }
	CBlockLayer&	GetBlockLayer(){ return m_BlockLayer; }
	CEventLayer&	GetEventLayer(){ return m_EventLayer; }


	//缩放地图
	void	SetScale(float scale);
	//滚动地图
	void	SetOffSet(int cx,int cy);
	//返回外接矩形尺寸
	CSize	GetBoundSize(){ return CSize((g_MapWidth + g_MapHeight)*g_TileWidth/2 ,(g_MapWidth + g_MapHeight)*g_TileHeight/2);}
	void	Destroy();
	
public:
	//地面层
	CTileLayer		m_TileLayer;
	//对象层
	CObjectLayer	m_ObjectLayer;
	//障碍层
	CBlockLayer		m_BlockLayer;
	//事件层
	CEventLayer		m_EventLayer;
	
};

