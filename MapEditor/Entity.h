#pragma once

//实体类，物体类，角色类，怪物类都从该类派生

class CEntity
{
public:
	CEntity();
	virtual ~CEntity(void);

	virtual void	Update(float fElapsedTime)=0;
	virtual void	Draw(CDC* pDC)=0;
	
	//进行缩放
	virtual void	SetScale(float scale){}
	//放置到地图上（x,y）位置
	virtual void	SetPos(int x,int y){ m_PosX = x;m_PosY=y; }
	virtual POINT	GetPos(){	POINT pt={m_PosX,m_PosY}; return pt; }
	//移动物体dx和dx个单位
	virtual void	Move(int dx,int dy){ m_PosX += dx;m_PosY +=dy; }
	//设置大小
	virtual void	SetSize(int width,int height){ m_Rect.right = m_Rect.left +width; m_Rect.bottom = m_Rect.top +height; }
	virtual CSize	GetSize(){ return m_Rect.Size(); }
	//设置绘制基准点坐标
	void	SetHotSpot(int x,int y){ m_HotX = x;	m_HotY = y;}
	CPoint	GetHotSpot(){	return CPoint(m_HotX,m_HotY); }
	//设置选中
	virtual void	SetChecked(bool bChecked){ m_bChecked = bChecked; }
	virtual bool	GetChecked(){ return m_bChecked; }
	virtual int		GetType(){ return m_Type; }
	//置空
	virtual void	SetEmpty();
public:
	//图片编号
	int		m_ResID;
	//在地图上的坐标
	int		m_PosX;
	int		m_PosY;
	
	CRect	m_Rect; //包围矩形

	int		m_HotX;
	int		m_HotY;
	//是否被鼠标选中
	bool	m_bChecked;
	//物体类型，0：场景物体，1：怪物，2：角色
	int		m_Type;
};

