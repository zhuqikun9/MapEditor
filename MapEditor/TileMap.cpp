#include "StdAfx.h"
#include "TileMap.h"
#include "MapEditor.h"


CTileMap::CTileMap(void)
{

}


CTileMap::~CTileMap(void)
{
	Destroy();
}
void	CTileMap::Create(int MapWidth,int MapHeight,int TileWidth,int TileHeight)
{
	Destroy();
	
	g_MapWidth=MapWidth;
	g_MapHeight=MapHeight;
	g_TileWidth=TileWidth;
	g_TileHeight=TileHeight;

	g_OrgTileWidth = TileWidth;
	g_OrgTileHeight = TileHeight;
	m_TileLayer.Create(MapWidth, MapHeight, TileWidth, TileHeight);
	//对象层初始化
	m_ObjectLayer.Create(MapWidth, MapHeight, TileWidth, TileHeight);
	//障碍层
	m_BlockLayer.Create(MapWidth, MapHeight, TileWidth, TileHeight);
	//事件层
	m_EventLayer.Create(MapWidth, MapHeight, TileWidth, TileHeight);
	
}
void	CTileMap::Update(float fElapsedTime)
{
	if(!g_bVisible||IsEmpty())
		return;

	m_ObjectLayer.Update(fElapsedTime);
}
void	CTileMap::Draw(CDC* pDC)
{
	if(!g_bVisible||IsEmpty())
		return;
	//地面层
	m_TileLayer.Draw(pDC);
//	if(g_bShowGrid)
		::DrawGrid(pDC);
	//对象层
	m_ObjectLayer.Draw(pDC);
	//障碍层
	m_BlockLayer.Draw(pDC);
	//事件层
	m_EventLayer.Draw(pDC);
	
}


//缩放
void	CTileMap::SetScale(float scale)
{	
	g_TileWidth = g_OrgTileWidth*scale; 
	g_TileHeight = g_OrgTileHeight*scale;
}

//设定地图整体偏移，cx横向偏移，cy纵向偏移
void	CTileMap::SetOffSet(int cx,int cy)
{
	g_offsetX =cx ;
	g_offsetY = cy;
}


void	CTileMap::Destroy()
{
	m_TileLayer.Destroy();
	//对象层
	m_ObjectLayer.Destroy();
	//障碍层
	m_BlockLayer.Destroy();
	//事件层
	m_EventLayer.Destroy();
}

bool CTileMap::SaveMapData(LPCTSTR filename)
{
	MAPHEADER MapHeader;
	MapHeader.MapWidth=g_MapWidth;
	MapHeader.MapHeight=g_MapHeight;
	MapHeader.TileWidth= g_TileWidth;
	MapHeader.TileHeight=g_TileHeight;
	MapHeader.SceneObjCount= m_ObjectLayer.GetObjSet().size();
	MapHeader.MonsterCount = m_ObjectLayer.GetMonsterSet().size();
	FILE* fp;
	if(0 != _tfopen_s(&fp, filename, _T("wb")))
		return false;

	//先存入文件头信息
	fwrite(&MapHeader,sizeof(MapHeader),1,fp);

	size_t	size = m_TileLayer.GetTileSet().size();
	CTile tile;
	//先存入TileLayer层数据
	for(size_t i=0;i<size;i++)
	{
		tile = m_TileLayer.GetTileSet().at(i);
		fwrite(&tile,sizeof(tile),1,fp);
	}

	//再存入ObjectLayer数据
	CSceneObj	obj;
	CRole		role;
	CMonster	monster;

	for(int i=0;i< MapHeader.SceneObjCount;i++)
	{	//判断物体类型
	
		obj = m_ObjectLayer.GetObjSet().at(i);
		//记录物体类型
		fwrite(&obj,sizeof(obj),1,fp);
	}

	for(int i=0;i< MapHeader.MonsterCount;i++)
	{
		monster = m_ObjectLayer.GetMonsterSet().at(i);
		fwrite(&monster,sizeof(monster),1,fp);
	}
		
	role = m_ObjectLayer.GetRole();	
	fwrite(&role,sizeof(role),1,fp);
	
	
	//再存入BlockLayer数据
	size = m_BlockLayer.GetBlockArray().size();
	for(size_t i=0;i<size;i++)
	{
		bool bPassable = m_BlockLayer.GetBlockArray().at(i);
		fwrite(&bPassable,sizeof(bPassable),1,fp);
	}
	//再存入EventLayer数据
	size = m_EventLayer.GetTriggerArray().size();
	fwrite(&size,sizeof(size),1,fp);
	for(size_t i=0;i<size;i++)
	{

		CTrigger trigger = m_EventLayer.GetTriggerArray().at(i);
		fwrite(&trigger,sizeof(trigger),1,fp);
	}

	fclose(fp);
	return true;
}

//加载地图数据
bool CTileMap::LoadMapData(LPCTSTR filename)
{
	FILE* fp;
	if(0 != _tfopen_s(&fp, filename, _T("rb")))
		return false;
	MAPHEADER MapHeader;
	fread(&MapHeader,sizeof(MapHeader),1,fp);
	Create(MapHeader.MapWidth,MapHeader.MapHeight,MapHeader.TileWidth,MapHeader.TileHeight);

	//先读取TileLayer层数据
	CTile tile;
	for(size_t i=0;i<m_TileLayer.GetTileSet().size();i++)
	{
		fread(&tile,sizeof(tile),1,fp);
		m_TileLayer.GetTileSet().at(i) = tile;
	}

	//再读取ObjectLayer数据
	
	CSceneObj	obj;
	CRole		role;
	CMonster	monster;
	for(int i=0;i<MapHeader.SceneObjCount;i++)
	{
			fread(&obj,sizeof(obj),1,fp);
			m_ObjectLayer.GetObjSet().push_back(obj);
	}

	for(int i=0;i<MapHeader.MonsterCount;i++)
	{
		fread(&monster,sizeof(monster),1,fp);
		m_ObjectLayer.GetMonsterSet().push_back(monster);
	}
	
	fread(&role,sizeof(role),1,fp);
	m_ObjectLayer.SetRole(role);
		
	//再读取BlockLayer数据
	bool bPassable;
	for(size_t i=0;i<m_BlockLayer.GetBlockArray().size();i++)
	{
		fread(&bPassable,sizeof(bPassable),1,fp);
		m_BlockLayer.GetBlockArray().at(i) = bPassable;
	}
	//再读取EventLayer数据
	int size = 0;
	fread(&size,sizeof(size),1,fp);
	for(int i=0;i<size;i++)
	{
		CTrigger trigger;
		fread(&trigger,sizeof(trigger),1,fp);
		m_EventLayer.GetTriggerArray().push_back(trigger);
	}

	fclose(fp);
	
	return true;
}



