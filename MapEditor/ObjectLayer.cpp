#include "StdAfx.h"
#include "BlockLayer.h"
#include "ObjectLayer.h"
#include "MapEditor.h"

void CSceneObj::Create(int ResID,INT PosX,INT PosY)
{
	m_ResID =ResID;
	m_PosX =PosX; m_PosY = PosY;

	int width = theApp.m_ResMgr.GetObj(ResID).GetWidth();
	int height = theApp.m_ResMgr.GetObj(ResID).GetHeight();
	CPoint destPos = MapToView(m_PosX,m_PosY);
	m_Rect.left = destPos.x;
	m_Rect.top = destPos.y;
	m_Rect.right = m_Rect.left+width;
	m_Rect.bottom = m_Rect.top+height;

	m_HotX = 0;
	m_HotY = height;
}
void CSceneObj::Update(float fElapsedTime)
{
	
}
void CSceneObj::Draw(CDC* pDC)
{
	if(m_ResID==-1)
		return;
	CPoint destPos = MapToView(m_PosX,m_PosY);

	m_Rect.MoveToXY(destPos);
//	m_Rect.OffsetRect(-m_HotX,-m_HotY);


	theApp.m_ResMgr.GetObj(m_ResID).SetHotSpot(m_HotX,m_HotY);
	m_Rect.OffsetRect(-m_HotX,-m_HotY);
	//如果被鼠标选中，则透明显示
	if(m_bChecked)
		theApp.m_ResMgr.GetObj(m_ResID).Draw(pDC,destPos.x,destPos.y+HALF_TILEHEIGHT,m_Rect.Width(),m_Rect.Height(),128);
	else
		theApp.m_ResMgr.GetObj(m_ResID).Draw(pDC,destPos.x,destPos.y+HALF_TILEHEIGHT,m_Rect.Width(),m_Rect.Height());
		

}


void CSceneObj::SetScale(float scale)
{
	if(m_ResID ==-1)
		return;
	//将尺寸记录下来
	int width = theApp.m_ResMgr.GetObj(m_ResID).GetWidth();
	int height = theApp.m_ResMgr.GetObj(m_ResID).GetHeight();
	width = int(width *scale);
	height = int(height * scale);
	SetSize(width ,height);
}

void CSceneObj::SetViewPos(int x,int y)
{
	m_Rect.MoveToXY(x,y);
	//int width = m_Rect.Width();
	//int height = m_Rect.Height();
	POINT  pt;
		//屏幕坐标转换为地图坐标
	pt = ViewToMap(x,y);
	if(pt.x>=0&&pt.x< g_MapWidth&&pt.y>=0&&pt.y< g_MapHeight )
		SetPos(pt.x,pt.y);
}

//自定义排序函数,
bool CompareZOrder(const CSceneObj& obj1, const CSceneObj& obj2)
{
  if(obj1.m_Rect.bottom<obj2.m_Rect.bottom)
	  return true;

  return false;
}

CObjectLayer::CObjectLayer()
{
	m_bVisible =true;
}
CObjectLayer::~CObjectLayer()
{
	Destroy();
}
void CObjectLayer::Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight)
{
	Destroy();

	m_ObjSet.resize(0);
	m_MonsterSet.resize(0);
}
//添加主角
void CObjectLayer::AddRole(float x,float y)
{
	if(x>=0&&x<g_MapWidth&&y>=0&&y<g_MapHeight )
	{
		//创建主角
		//if(m_Role.m_ResID==-1)
		//	return;
		////设置投放地点
		//m_Role.Create(x,y);
		////指定方向
		//m_Role.SetDirection(rand()%16);

	}
}
//添加怪物
void	CObjectLayer::AddMonster(int ResId,int x,int y)
{
	if(ResId==-1)
		return;
	POINT  pt;
	//屏幕坐标转换为地图坐标
	pt = ViewToMap(x,y);
	if(pt.x>=0&&pt.x<g_MapWidth&&pt.y>=0&&pt.y<g_MapHeight )
	{
		CMonster pMonster;
	
		pMonster.Create(ResId,pt.x,pt.y);

		//随机生成一个方向
		pMonster.SetDirection(rand()%16);
		m_MonsterSet.push_back(pMonster);
	}
}


//添加物体
void CObjectLayer::AddObject(CSceneObj& obj)
{
	int index=-1;
	//判断位置是否重合
	for(size_t i = 0;i<m_ObjSet.size();i++) 
	{
		if (m_ObjSet.at(i).m_PosX == obj.m_PosX&&m_ObjSet.at(i).m_PosY==obj.m_PosY)
		{
			index = i;
			break;
		}
	}
	if(index!=-1)
		m_ObjSet.at(index) = obj;
	else
		m_ObjSet.push_back(obj);
	
}

void CObjectLayer::Update(float fElapsedTime)
{
	if(m_ObjSet.size()==0)
		return;
	for(size_t i=0;i<m_ObjSet.size();i++)
		m_ObjSet[i].Update(fElapsedTime);
	//角色更新，待以后完善
//	m_Role.Update(fElapsedTime);
	ZOrderSort();
}

void CObjectLayer::Draw(CDC* pDC)
{
	if(!m_bVisible||m_ObjSet.size()==0)
		return;
	//先对所有物体的深度值按从大到小的顺序进行深度排序，深度值大的被深度值小的遮挡，就能实现遮挡效果
	
	//按照深度值从大到小的顺序贴图
	for(size_t i=0;i<m_ObjSet.size();i++)
		m_ObjSet[i].Draw(pDC);
	//画角色，待以后完善
//	m_Role.Draw(pDC);
}
//使用STL自带的排序函数，对CEntity*数组按照深度值从大到小顺序排序
void CObjectLayer::ZOrderSort()
{
	sort(m_ObjSet.begin(),m_ObjSet.end(),CompareZOrder);
}
//tile尺寸都一样，物体每个大小都不同
void CObjectLayer::SetSize(int index,int width,int height)
{
	int ResID = m_ObjSet.at(index).m_ResID;
	if(ResID ==-1)
		return;
	//将尺寸记录下来
	m_ObjSet.at(index).SetSize(width,height);

}

//删除一个物体
void CObjectLayer::DelObject(int index)
{
	if(index!=-1)
		m_ObjSet.erase(m_ObjSet.begin()+index);
}

void CObjectLayer::DelObject(CSceneObj obj)
{
	for(vector<CSceneObj>::iterator it = m_ObjSet.begin();it!= m_ObjSet.end();) 
	{
		if (*it == obj)
			it = m_ObjSet.erase(it++);
		else
			it++;
	}
	
}

//判断对应屏幕上(x,y)处的地图上的物体是否被选中
int CObjectLayer::GetCurIndex(CPoint point)
{
	//将上一次选中物体置于非选中状态
	for(size_t i=0;i<m_ObjSet.size();i++)
		m_ObjSet.at(i).SetChecked(false);

	for(size_t i=0;i<m_ObjSet.size();i++)
		if(m_ObjSet.at(i).m_Rect.PtInRect(point))
		{
			m_ObjSet.at(i).SetChecked(true);
			return i;
		}
		
	return -1;
}

CSceneObj*	CObjectLayer::GetCurChose(CPoint point)
{

	for(size_t i=0;i<m_ObjSet.size();i++)
		m_ObjSet.at(i).SetChecked(false);
	
	for(size_t i=0;i<m_ObjSet.size();i++)
		if(m_ObjSet.at(i).m_Rect.PtInRect(point))
		{
			m_ObjSet.at(i).SetChecked(true);
			return &m_ObjSet.at(i);
		}
		
	return NULL;
}

CSceneObj* CObjectLayer::GetSceneObj(CSceneObj obj)
{
	
	for(size_t i=0;i<m_ObjSet.size();i++)
	{
		if(m_ObjSet.at(i)==obj)
			return &m_ObjSet.at(i);
	}
	return NULL;
}

void CObjectLayer::SetScale(float scale)
{

	for(size_t i=0;i<m_ObjSet.size();i++)
	{
		m_ObjSet.at(i).SetScale(scale);
	}

}

void CObjectLayer::Destroy()
{	
	
	m_ObjSet.clear(); 
	m_MonsterSet.clear();
}