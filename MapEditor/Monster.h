#pragma once
#include "Animation.h"
#include "Role.h"
//预留接口，暂时没有用


class CMonster:public CRole
{
public:
	CMonster(void);
	~CMonster(void);
	void	Create(int ResID,int PosX,int PosY);
	void	Update(float fElapsedTime);
	void	Draw(CDC* pDC);

	//更新行走动作
	void	UpdateWalk(float fElapsedTime);
	////更新攻击动作
	//void	UpdateAttack(float fElapsedTime);
	//检测距离
	void	DetectDistance(CRole *role);
public:
	int		m_fDistance;
};

