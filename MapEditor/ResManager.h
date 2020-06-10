#pragma once

#include "Texture.h"
#include "Animation.h"
#include "Sprite.h"
#include "Monster.h"

//资源管理类，对所有的场景资源集中管理
class CResManager
{
public:
	CResManager(void);
	~CResManager(void);
	//加载场景资源
	void	LoadSceneRes();

	void	LoadSpriteRes();
	//返回瓷砖tile图片集合
	CArray<CTexture>& GetTileRes(){ return m_TileImages; }
	//返回物体图片集合
	CArray<CTexture>& GetObjRes(){ return m_ObjImages; }
	//返回怪物集合
	CArray<CSprite>&  GetMonsterRes(){ return m_MonsterSet; }
	//返回编号为index的tile图片
	CTexture&		GetTile(int index){ return m_TileImages.GetAt(index); }
	//返回编号为index的物体图片
	CTexture&		  GetObj(int index){ return m_ObjImages.GetAt(index); }
	//释放资源
	void	Destroy();
	//将指定目录下的图片文件全部加载到图片数组中
	void	LoadImages(CArray<CTexture>& imglist,CString strPath);

public:
	//存放瓷砖tile的图片数组
	CArray<CTexture> m_TileImages;
	//存放物体的图片数组
	CArray<CTexture> m_ObjImages;
	//碰撞块标记图片
	CTexture		m_BlockImage;
	//触发器标记图片
	CTexture		m_TriggerImage;

	CArray<CTexture> m_SpriteThumb;
	CArray<CSprite> m_MonsterSet;

	CSprite			m_Role;
	

};

