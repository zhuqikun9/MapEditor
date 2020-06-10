#include "StdAfx.h"
#include "Monster.h"
#include "MapEditor.h"
#include "BlockLayer.h"
CMonster::CMonster(void)
{
	m_fDistance = 100;
	m_Type = 1;
}


CMonster::~CMonster(void)
{
	
}
void	CMonster::Create(int ResID,int PosX,int PosY)
{
	m_ResID =ResID;
	m_PosX =PosX; m_PosY = PosY;

}
void	CMonster::Update(float fElapsedTime)
{
	if(!m_bVisible)
		return;
	UpdateWalk(fElapsedTime);
	theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).UpdateDirection(m_Direction);
	theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).Update(fElapsedTime);

	
}
void CMonster::Draw(CDC* pDC)
{
	if(!m_bVisible)
		return;
	CPoint destPos;
	destPos =  MapToView(m_PosX,m_PosY);
	theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).Draw(pDC,destPos.x,destPos.y);
}



//检测距离
void	CMonster::DetectDistance(CRole *role)
{
	POINT  RolePos = role->GetPos();
	int dx = m_PosX - RolePos.x;
	int dy = m_PosY - RolePos.y;
	m_fDistance = dx*dx + dy*dy;
}


//更新行走动作
void	CMonster::UpdateWalk(float fElapsedTime)
{
	static float m_fSinceLastFrame = 0.0f;
	
	m_fSinceLastFrame += fElapsedTime;//累加时间片段
	
	//当时间差大于10秒钟，随机变化方向
	if(m_fSinceLastFrame >= 5.0f)
	{
		int dir=(rand()%16);
		SetDirection(rand()%16);
		for(int i=0;i<10;i++)
		{
			switch (dir)
			{
			case 0:
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).SetState(MOVE);
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).m_WalkAni.NextFrame(fElapsedTime);	
				if(CanPass(1,1))
					Move(1,1);
				break;
			case 1:
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).SetState(MOVE);
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).m_WalkAni.NextFrame(fElapsedTime);
				if(CanPass(-1,-1))
					Move(-1,-1);
				break;
			case 2:
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).SetState(MOVE);
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).m_WalkAni.NextFrame(fElapsedTime);
				if(CanPass(0,1))
					Move(0,1);
				break;
		
			case 3:
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).SetState(MOVE);
				theApp.m_ResMgr.m_MonsterSet.GetAt(m_ResID).m_WalkAni.NextFrame(fElapsedTime);
				if(CanPass(0,-1))
					Move(0,-1);
				break;
			default:
				break;
			}
		}
		m_fSinceLastFrame =0;
	}
}

