#include "StdAfx.h"
#include "EventLayer.h"
#include "MapEditor.h"

CEventLayer::CEventLayer(void)
{
	m_bVisible =true;
}


CEventLayer::~CEventLayer(void)
{
	Destroy();
}
void CEventLayer::Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight)
{
	Destroy();

	m_TriggerArray.resize(0);
	
}
void CEventLayer::Draw(CDC* pDC)
{
	if(!m_bVisible)
		return;
	POINT pt;
	for(size_t i=0;i<m_TriggerArray.size();i++)
	{
		int x = m_TriggerArray.at(i).GetPosX();
		int y = m_TriggerArray.at(i).GetPosY();
		pt = GridToView(x,y);
		theApp.m_ResMgr.m_TriggerImage.Draw(pDC,pt.x,pt.y,g_GridWidth,g_GridHeight);
	}

}

//判断位于地图（x，y）处是否是触发器
bool CEventLayer::IsTrigger(int x,int y)
{	//遍历触发器数组，判断是否有触发器坐标与指定坐标重合
	for(size_t i=0;i<m_TriggerArray.size();i++)
		if(m_TriggerArray.at(i).GetPosX()==x&&m_TriggerArray.at(i).GetPosY()==y)
			return true;
	return false;
}

CTrigger& CEventLayer::GetTriggerByID(int id)
{
	for(size_t i=0;i<m_TriggerArray.size();i++)
		if(m_TriggerArray.at(i).GetTriggerID() == id)
			return m_TriggerArray.at(i);
	return CTrigger(0,0,0,0,0);
}

//删除位于地图上（x，y）处的触发器
void CEventLayer::DelTrigger(int x,int y)
{

	for(size_t i=0;i<m_TriggerArray.size();i++)
		if(m_TriggerArray.at(i).GetPosX()==x&&m_TriggerArray.at(i).GetPosY()==y)
		{
			m_TriggerArray.erase(m_TriggerArray.begin()+ i);
			return;
		}
}