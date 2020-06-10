#include "StdAfx.h"
#include "Entity.h"
#include "BlockLayer.h"

CEntity::CEntity():m_ResID(-1),m_PosX(0),m_PosY(0),m_bChecked(0),m_Type(-1)
{

	m_Rect.SetRectEmpty();
	m_HotX = m_HotY = 0;
}


CEntity::~CEntity(void)
{
}

//÷√ø’
void CEntity::SetEmpty()
{
	m_ResID=(-1);
	m_PosX = 0;
	m_PosY = 0;
	
	m_bChecked = 0;
	m_Type = -1;

	m_Rect.SetRectEmpty();
}
