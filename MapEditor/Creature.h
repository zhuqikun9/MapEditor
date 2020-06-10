#pragma once
#include "Entity.h"

//预留接口，暂时没什么用

class CCreature:public CEntity
{
public:
	CCreature(void);
	~CCreature(void);

	void	Create(int PosX,int PosY);
	void	Update(float fElapsedTime);
	void	Draw(CDC* pDC);
	void	SetDirection(int dir){ 	m_Direction = dir; }
	bool	CanPass(int dx,int dy);

public:
	bool	m_bVisible;
	//面对方向
	int			m_Direction;
};

