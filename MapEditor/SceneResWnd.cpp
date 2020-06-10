// SceneWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor.h"
#include "SceneResWnd.h"
#include "MapEditorDoc.h"
#include "MainFrm.h"
#define IDC_TABCTRL			11

// CSceneResWnd

IMPLEMENT_DYNAMIC(CSceneResWnd, CDockablePane)

CSceneResWnd::CSceneResWnd()
{

}

CSceneResWnd::~CSceneResWnd()
{
}


BEGIN_MESSAGE_MAP(CSceneResWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()

END_MESSAGE_MAP()



// CSceneResWnd 消息处理程序


int CSceneResWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建选项卡窗口:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D_ONENOTE , rectDummy, this, 11))
	{
		TRACE0("未能创建选项卡窗口\n");
		return -1;      // 未能创建
	}
	//创建瓷砖缩略图面板
	m_TileDlg.Create(NULL,_T(""),WS_VISIBLE | WS_CLIPCHILDREN, rectDummy, &m_wndTabs,12);//.Create(IDD_THUMBDLG,&m_wndTabs);
	m_TileDlg.CreateThumbList(theApp.m_ResMgr.GetTileRes(),64,32);
	
	//创建场景物体缩略图面板
	m_ObjectDlg.Create(NULL,_T(""),WS_VISIBLE | WS_CLIPCHILDREN, rectDummy, &m_wndTabs,13);
	m_ObjectDlg.CreateThumbList(theApp.m_ResMgr.GetObjRes());
	//怪物面板
	m_SpriteDlg.Create(NULL,_T(""),WS_VISIBLE | WS_CLIPCHILDREN, rectDummy, &m_wndTabs,14);
	m_SpriteDlg.CreateThumbList(theApp.m_ResMgr.m_SpriteThumb);


	//NPC面板
//	m_NpcDlg.Create(IDD_THUMBDLG,&m_wndTabs);
//	m_NpcDlg.CreateThumbList(theApp.m_ResMgr.GetNpcSet());
	// 将瓷砖缩略图窗口附加到选项卡:
	m_wndTabs.AddTab(&m_TileDlg, _T("地面"), (UINT)0, FALSE);
	// 将场景物体缩略图窗口附加到选项卡:
	m_wndTabs.AddTab(&m_ObjectDlg, _T("物体"), (UINT)1,FALSE);

	m_wndTabs.AddTab(&m_SpriteDlg, _T("怪物"), (UINT)2,FALSE);
	
	//m_wndTabs.AddTab(&m_NpcDlg,_T("NPC"), (UINT)3, FALSE);

	AdjustLayout();
	
	return 0;
}


void CSceneResWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AdjustLayout();
}

void CSceneResWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndTabs.SetWindowPos (this, -1, -1, rectClient.Width(), rectClient.Height(), SWP_NOMOVE | SWP_NOZORDER);

}



BEGIN_MESSAGE_MAP(CTileThumbDlg, CThumbWnd)
	ON_NOTIFY(NM_CLICK,IDC_THUMBLIST,OnSelectListItem)
END_MESSAGE_MAP()

void CTileThumbDlg::OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapEditorDoc* pDoc = (CMapEditorDoc*)pFrame->GetActiveDocument();
	m_iCurSelItem = pNMLV->iItem;
	if(m_iCurSelItem!=-1&&!::IsEmpty())
	{
		pDoc->OnLayerTile();
		pDoc->m_CurSelObj = m_iCurSelItem;

	}

	*pResult = 0;
}

BEGIN_MESSAGE_MAP(CObjThumbDlg, CThumbWnd)
	ON_NOTIFY(NM_CLICK,IDC_THUMBLIST,OnSelectListItem)
END_MESSAGE_MAP()

void CObjThumbDlg::OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapEditorDoc* pDoc = (CMapEditorDoc*)pFrame->GetActiveDocument();
	m_iCurSelItem = pNMLV->iItem;
	if(m_iCurSelItem!=-1&&!::IsEmpty())
	{
		pDoc->OnLayerObject();
		pDoc->m_CurSelObj = m_iCurSelItem;
		
	}

	*pResult = 0;
}

BEGIN_MESSAGE_MAP(CSpriteThumbDlg, CThumbWnd)
	ON_NOTIFY(NM_CLICK,IDC_THUMBLIST,OnSelectListItem)
END_MESSAGE_MAP()

void CSpriteThumbDlg::OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapEditorDoc* pDoc = (CMapEditorDoc*)pFrame->GetActiveDocument();
	m_iCurSelItem = pNMLV->iItem;
	if(m_iCurSelItem!=-1&&!::IsEmpty())
	{
		pDoc->OnLayerObject();

	}

	*pResult = 0;
}