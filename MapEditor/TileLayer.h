#pragma once

#include "Layer.h"

//瓷砖类，地板砖
class CTile
{
public:
	CTile():m_ResID(-1),m_PosX(0),m_PosY(0){}
	~CTile(){}

	void	Draw(CDC* pDC);
	//返回瓷砖对应的图片编号
	int		GetResID(){ return m_ResID; }
	//设定瓷砖图片编号
	void	SetResID(int ResID){ m_ResID = ResID; }
	//返回瓷砖在地图上的位置
	CPoint	GetPos(){	return CPoint(m_PosX,m_PosY); }
	//设定瓷砖位置
	void	SetPos(int x,int y){ m_PosX = x;m_PosY=y; }

	//置空
	void	SetEmpty(){ m_ResID=-1;m_PosX=0;m_PosY=0; }
public:
	//瓷砖对应的图片编号
	int		m_ResID;
	//在地图上的坐标
	int		m_PosX;
	int		m_PosY;

	int		m_HotX;
	int		m_HotY;
	
};


//地面层
class CTileLayer
{
public:
	CTileLayer();
	virtual ~CTileLayer();
	//创建地面层
	void	Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight);
	//绘制
	void	Draw(CDC* pDC);

	//删除屏幕上（x,y）处的瓷砖
	void	DelTile(int x,int y);
	//贴瓷砖，参数为图片的编号，屏幕坐标
	void	AddTile(int ResID,int x,int y);	

	void	Destroy(){	m_TileSet.clear(); }

	//设置地图是否可见
	void	SetVisible(bool bVisible){ m_bVisible = bVisible; }
	//返回地图是否可见
	bool	GetVisible(){ return m_bVisible; }

	//返回瓷砖数组
	vector<CTile>& GetTileSet(){ return m_TileSet; }
protected:
	//瓷砖数组
	vector<CTile>	m_TileSet;
	bool			m_bVisible;
};