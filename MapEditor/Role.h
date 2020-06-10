#pragma once
//#include "Animation.h"
#include "Entity.h"

//预留接口，暂时没有用
class CRole:public CEntity
{
public:
	CRole();
	~CRole(void);
	void	Create(int PosX,int PosY);
	void	Update(float fElapsedTime);
	void	Draw(CDC* pDC);
	void	SetDirection(int dir){ 	m_Direction = dir; }
	bool	CanPass(int dx,int dy);

public:
	bool	m_bVisible;
	//面对方向
	int		m_Direction;
};

