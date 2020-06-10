#pragma once
#include <vector>
using std::vector;

#include "Layer.h"

//障碍物层，控制地图是否可以通过
class CBlockLayer 
	
{
public:
	CBlockLayer(void);
	~CBlockLayer(void);
	//取得当前类的对象的实例
	static  CBlockLayer*  GetInstance(){ return s_BlockLayer; }
	void	Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight);

	void	Draw(CDC* pDC);
	//设定能否通过
	void	SetPassable(int x,int y,bool bPassable){ m_bBlockArray.at(x+y*m_Width)= bPassable; }
	//判断地图（x,y）格子能否通过
	bool	IsPassable(int x,int y){	return m_bBlockArray.at(x+y*m_Width); }

	//设置地图是否可见
	void	SetVisible(bool bVisible){ m_bVisible = bVisible; }
	//返回地图是否可见
	bool	GetVisible(){ return m_bVisible; }
	void	Destroy(){	m_bBlockArray.clear(); }

	vector<bool>& GetBlockArray(){ return m_bBlockArray; }
protected:
	//障碍物数组，true表示可以通过，false表示不可通过
	vector<bool> m_bBlockArray;
	//每行个数
	int			m_Width;
	//每列个数
	int			m_Height;

	bool		m_bVisible;
	static CBlockLayer* s_BlockLayer;
};

inline CBlockLayer* BlockLayer(){	return CBlockLayer::GetInstance(); }