#pragma once
#include <algorithm>
#include <vector>
using std::vector;
#include "Layer.h"
#include "Entity.h"
#include "Role.h"
#include "Monster.h"

//物体类
class CSceneObj:public CEntity
{
public:
	CSceneObj(){ m_Type = 0;}
	~CSceneObj(){}
	BOOL operator==(const CSceneObj& obj) const throw()
	{
		return (m_Rect==obj.m_Rect);
	}

	void	Create(int ResID,INT PosX,INT PosY);
	void	Update(float fElapsedTime);
	void	Draw(CDC* pDC);
	//设置缩放
	void	SetScale(float scale);

	void	SetViewPos(int x,int y);

};


//物体图层类，每个地图最多可放置MapWidth*MapHeight个物体
class CObjectLayer 
{
public:
	CObjectLayer(void);
	~CObjectLayer(void);
	void	Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight);
	void	Update(float fElapsedTime);
	//绘制
	void	Draw(CDC* pDC);
	//深度排序
	void	ZOrderSort();

	//删除第index个物体
	void	DelObject(int index);
	//删除指定的物体
	void	DelObject(CSceneObj obj);

	//添加物体
	void	AddObject(CSceneObj& obj);
	//添加主角
	void	AddRole(float x,float y);
	//添加怪物
	void	AddMonster(int ResId,int x,int y);
	//设定地图上（x,y）处物体的尺寸,
	void	SetSize(int index,int width,int height);

	void	SetScale(float scale);
	void	Destroy();

	//设置地图是否可见
	void	SetVisible(bool bVisible){ m_bVisible = bVisible; }
	//返回地图是否可见
	bool	GetVisible(){ return m_bVisible; }
	//获取当前地图上被选中的物体的数组索引，若未选中，返回-1
	int		GetCurIndex(CPoint point);
	CSceneObj*		GetCurChose(CPoint point);

	CSceneObj*		GetSceneObj(CSceneObj obj);
	CRole&	GetRole(){	return m_Role;	}
	void	SetRole(CRole& role){ if(m_Role.m_ResID==-1) m_Role = role; }
	vector<CSceneObj>& GetObjSet(){	return m_ObjSet; }
	vector<CMonster>&  GetMonsterSet(){	return m_MonsterSet; }
protected:
	vector<CSceneObj>	m_ObjSet;
	vector<CMonster>	m_MonsterSet;
	//游戏中存在的唯一一个主角
	CRole	 m_Role;
	
	bool	m_bVisible;
};

