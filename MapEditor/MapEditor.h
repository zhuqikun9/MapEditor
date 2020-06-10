
// MapEditor.h : MapEditor 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "ResManager.h"

// CMapEditorApp:
// 有关此类的实现，请参阅 MapEditor.cpp
//

class CMapEditorApp : public CWinAppEx
{
public:
	CMapEditorApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	BOOL  m_bHiColorIcons;
	//资源管理类
	CResManager m_ResMgr;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapEditorApp theApp;
