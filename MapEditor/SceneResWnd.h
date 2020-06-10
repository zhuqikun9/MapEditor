#pragma once
#include <vector>
using std::vector;
//#include "ThumbDlg.h"
#include "ThumbWnd.h"


class CSceneToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CTileThumbDlg:public CThumbWnd
{
protected:
	DECLARE_MESSAGE_MAP()
	void OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult);
};

class CObjThumbDlg:public CThumbWnd
{
protected:
	DECLARE_MESSAGE_MAP()
	void OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult);
};

class CSpriteThumbDlg:public CThumbWnd
{
protected:
	DECLARE_MESSAGE_MAP()
	void OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult);
};
//场景资源停靠面板
class CSceneResWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CSceneResWnd)

public:
	CSceneResWnd();
	virtual ~CSceneResWnd();
	//适应布局
	void AdjustLayout();

protected:
	//选项卡控件
	CMFCTabCtrl	m_wndTabs;
	//地砖缩略图子窗口
	CTileThumbDlg	m_TileDlg;
	//物体缩略图子窗口
	CObjThumbDlg	m_ObjectDlg;
	//怪物缩略图子窗口
	CSpriteThumbDlg	m_SpriteDlg;

public:

	//返回当选中瓷砖图片编号
	int		GetCurSelTileIndex(){ return m_TileDlg.GetCurSelResID(); }
	//返回当前选中的物体图片编号
	int		GetCurSelObjectIndex(){ return m_ObjectDlg.GetCurSelResID(); }
	//返回当前选中的动物编号
	int		GetCurSelSpriteIndex(){ return m_SpriteDlg.GetCurSelResID(); }
	//返回当前选中选项卡索引
	int		GetCurSetTab(){ return m_wndTabs.GetActiveTab(); }
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);



};


