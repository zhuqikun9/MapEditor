#pragma once
#include "Animation.h"


enum SPRITESTATE
{
	STAND = 0,
	MOVE  = 1,
	FIGHT = 2,
	DEATH = 3,
};
//精灵类。说明：每个精灵包含4组动画，分别是站立，行走，打斗，死亡倒地动画序列

class CSprite
{
public:
	CSprite(void);
	~CSprite(void);
	void	Create(LPCSTR AniFile);

	void	Update(float fElapsedTime);
	void	Draw(CDC* pDC,int xDest,int yDest);

	//碰撞检测
	bool	CollidesWith(CSprite& spr) ; 
	
	void	SetState(SPRITESTATE state){ m_State= state; }
	
	
	void	UpdateDirection(int direction);
	//更新行走动作
	void	UpdateWalk(float fElapsedTime);
	//更新攻击动作
	void	UpdateAttack(float fElapsedTime);
	//更新站立动作
	void	UpdateStand(float fElapsedTime);
	//更新死亡动作
	void	UpdateDeath(float fElapsedTime);
public:
	//站立动画序列
	CAnimation		m_StandAni;
	//行走动画序列
	CAnimation		m_WalkAni;
	//攻击动画序列
	CAnimation		m_AttackAni;
	//死亡倒地动画
	CAnimation		m_DeathAni;

	//精灵状态
	SPRITESTATE	m_State;
	
	//是否正在攻击
	bool		m_bIsAttack;
};

