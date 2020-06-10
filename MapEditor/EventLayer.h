#pragma once
#include "Layer.h"

//地图事件层，指定在何位置触发场景转换,

//触发器结构
class CTrigger
{
public:
	CTrigger():m_TriggerID(0),m_PosX(0),m_PosY(0),m_MapID(0),m_iStartX(0),m_iStartY(0),m_Direction(0){}
	CTrigger(int TriggrtID,int MapID,int startX,int startY,int dir):m_TriggerID(TriggrtID),
				m_MapID(MapID),m_iStartX(startX),m_iStartY(startY),m_Direction(dir){ m_PosX=0;m_PosY = 0;}
	CTrigger& operator =(const CTrigger& trigger)
	{
		if(&trigger==this)
			return *this;
		m_TriggerID = trigger.m_TriggerID;;
		m_PosX = trigger.m_PosX;
		m_PosY = trigger.m_PosY;
		m_MapID = trigger.m_MapID;
		m_iStartX = trigger.m_iStartX;
		m_iStartY = trigger.m_iStartY;
		m_Direction = trigger.m_Direction;
		return *this;
	}
	~CTrigger(){}

	int		GetTriggerID(){ return m_TriggerID; }
	int		GetPosX(){ return m_PosX; }
	int		GetPosY(){ return m_PosY; }
	int		GetMapID(){ return m_MapID; }
	int		GetStartPosX(){ return m_iStartX; }
	int		GetStartPosY(){ return m_iStartY; }
	int		GetDirection(){ return m_Direction; }

	void	SetTriggerID(int id){  m_TriggerID = id; }
	void	SetPosX(int x){ m_PosX = x; }
	void	SetPosY(int y){ m_PosY = y; }
	void	SetMapID(int id){ m_MapID = id; }
	void	SetStartPosX(int startX){  m_iStartX = startX; }
	void	SetStartPosY(int startY){  m_iStartY = startY; }
	//0~7分别表示8个方向
	void	SetDirection(int dir){  m_Direction = dir; }
public:
	int		m_TriggerID; //触发器ID编号
	int		m_PosX;		//触发器在地图上的X坐标
	int		m_PosY;		//触发器在地图上的Y坐标
	int		m_MapID; //指向待传送的地图文件名
	int		m_iStartX;	//传送到另一个地图后的主角起始X坐标
	int		m_iStartY;	//传送到另一个地图后的主角起始Y坐标
	int		m_Direction;	//传送到另一个地图后的主角面对的方向
	
};


//事件层
class CEventLayer
{
public:
	CEventLayer(void);
	~CEventLayer(void);
	//创建
	void	Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight);
	//绘制
	void	Draw(CDC* pDC);
	//返回触发器数组
	vector<CTrigger>& GetTriggerArray(){ return m_TriggerArray; }
	//更加ID获取触发器
	CTrigger& GetTriggerByID(int id);
	//设置触发器
	void	AddTrigger(CTrigger& trigger){	m_TriggerArray.push_back(trigger);	}
	//删除位于地图上（x，y）处的触发器
	void	DelTrigger(int x,int y);
	//判断位于地图（x，y）处是否是触发器
	bool	IsTrigger(int x,int y);
	//释放
	void	Destroy(){	m_TriggerArray.clear(); }

	//设置地图是否可见
	void	SetVisible(bool bVisible){ m_bVisible = bVisible; }
	//返回地图是否可见
	bool	GetVisible(){ return m_bVisible; }
protected:
	//触发器数组，地图上任意一个图块都有可能是触发器
	vector<CTrigger> m_TriggerArray;
	bool			m_bVisible;
};

