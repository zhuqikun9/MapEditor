#include "StdAfx.h"
#include "ResManager.h"


CResManager::CResManager(void)
{

}

CResManager::~CResManager(void)
{
	Destroy();
}

void CResManager::LoadSceneRes()
{
	Destroy();
	LoadImages(m_TileImages,CIniFile::GetIniFileString(_T("ResoursePath"),_T("TilePath")));
	LoadImages(m_ObjImages,CIniFile::GetIniFileString(_T("ResoursePath"),_T("ObjectPath")));
	LoadImages(m_ObjImages,CIniFile::GetIniFileString(_T("ResoursePath"),_T("BuildingPath")));	
	LoadImages(m_ObjImages,CIniFile::GetIniFileString(_T("ResoursePath"),_T("NpcPath")));
	//路障标记图片
	m_BlockImage.Create(CIniFile::GetIniFileString(_T("ResoursePath"),_T("BlockPath")));
	//触发器标记图片
	m_TriggerImage.Create(CIniFile::GetIniFileString(_T("ResoursePath"),_T("TriggerPath")));
}
void CResManager::LoadSpriteRes()
{
	//加载怪物缩略图
	LoadImages(m_SpriteThumb,CIniFile::GetIniFileString(_T("ResoursePath"),_T("MonsterThumbPath")));

	m_Role.Create("Data/Hero/角色.xml");
	CSprite Monster;
	Monster.Create("Data/Monster/boss.xml");
	m_MonsterSet.Add(Monster);
	Monster.Create("Data/Monster/娜迦.xml");
	m_MonsterSet.Add(Monster);
	Monster.Create("Data/Monster/小怪.xml");
	m_MonsterSet.Add(Monster);
	Monster.Create("Data/Monster/蝎子.xml");
	m_MonsterSet.Add(Monster);
	Monster.Create("Data/Monster/骷髅兵.xml");
	m_MonsterSet.Add(Monster);
	
}

void CResManager::Destroy()
{
	m_TileImages.RemoveAll();

	m_ObjImages.RemoveAll();

}

void CResManager::LoadImages(CArray<CTexture>& imglist,CString strPath)
{
	//搜索该文件目录下的所有图片文件，将文件名存入字符串数组中
	CFileFind	finder;
	BOOL bWorking = finder.FindFile(strPath+_T("*.*"));
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDirectory())
			continue;
		CString fileName = finder.GetFileName();
		LPCTSTR pszExt = _tcsrchr(fileName,_T('.'));
		if(pszExt)
		{	//此为CImage支持的格式
			if((_tcsicmp(pszExt,_T(".bmp")) == 0)||(_tcsicmp(pszExt,_T(".png")) == 0)
					||(_tcsicmp(pszExt,_T(".tif")) == 0)||(_tcsicmp(pszExt,_T(".tiff")) == 0)
					||(_tcsicmp(pszExt,_T(".jpg")) == 0)||(_tcsicmp(pszExt,_T(".jpeg")) == 0)
					||(_tcsicmp(pszExt,_T(".gif")) == 0))
			{
				CTexture image;
				image.Create(strPath+fileName);
				imglist.Add(image);
			}
		}
	}
	finder.Close();
}

