#include "StdAfx.h"
#include "Creature.h"
#include "BlockLayer.h"
#include "MapEditor.h"

CCreature::CCreature(void)
{
}


CCreature::~CCreature(void)
{
}
void	CCreature::Create(int PosX,int PosY)
{
	m_PosX =PosX; m_PosY = PosY;

}

bool	CCreature::CanPass(int dx,int dy)
{
	//计算下一步的坐标，落在地图那个格子里
	int iPosX = m_PosX+dx;
	int iPosY = m_PosY+dy;
	int width =g_MapWidth;
	int height =g_MapHeight;
	if(iPosX<width&&iPosX>=0&&iPosY<height&&iPosY>=0)
	{//障碍物数组，true表示可以通过，false表示不可通过
		if(CBlockLayer::GetInstance()->IsPassable(iPosX,iPosY))
			return true;
	}
	return false;
}

void	CCreature::Update(float fElapsedTime)
{
	if(!m_bVisible)
		return;
	theApp.m_ResMgr.m_Role.UpdateDirection(m_Direction);
	theApp.m_ResMgr.m_Role.Update(fElapsedTime);
	
}
void CCreature::Draw(CDC* pDC)
{
	if(!m_bVisible)
		return;
	CPoint destPos;
	destPos =  MapToView(m_PosX,m_PosY);
	theApp.m_ResMgr.m_Role.Draw(pDC,destPos.x,destPos.y);
}
