
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MapEditor.h"
#include "MapEditorDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()

	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序
//
//int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	CRect rectDummy;
//	rectDummy.SetRectEmpty();
//
//	//创建属性网格
//	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
//	{
//		TRACE0("未能创建属性网格\n");
//		return -1;      // 未能创建
//	}
//
//	InitPropList();
//	
//	AdjustLayout();
//	return 0;
//}
//
//void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
//{
//	CDockablePane::OnSize(nType, cx, cy);
//	AdjustLayout();
//}
//void CPropertiesWnd::AdjustLayout()
//{
//	if (GetSafeHwnd() == NULL)
//	{
//		return;
//	}
//
//	CRect rectClient;
//	GetClientRect(rectClient);
//
//	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top , rectClient.Width(), rectClient.Height() , SWP_NOACTIVATE | SWP_NOZORDER);
//}
//
//
//
//void CPropertiesWnd::InitPropList()
//{
//	SetPropListFont();
//
//	m_wndPropList.EnableHeaderCtrl(FALSE);
//	m_wndPropList.EnableDescriptionArea();
//	m_wndPropList.SetVSDotNetLook();
//	m_wndPropList.MarkModifiedProperties();
//
//	
//	//地图属性组
//	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("地图属性"));
//	//地图宽和高为只读属性，在创建地图时指定，之后不可更改
//	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("地图宽度"), (_variant_t)0, _T("地图横向单元格个数"));
//	pProp->AllowEdit(FALSE);
//	pGroup1->AddSubItem(pProp);
//
//	pProp = new CMFCPropertyGridProperty( _T("地图高度"), (_variant_t)0, _T("地图纵向单元格个数"));
//	pProp->AllowEdit(FALSE);
//	pGroup1->AddSubItem(pProp);
//
//	pProp = new CMFCPropertyGridProperty(_T("图块宽度"), (_variant_t)0, _T("单元格图块的宽度"));
//	pProp->AllowEdit(FALSE);
//	pGroup1->AddSubItem(pProp);
//	pProp = new CMFCPropertyGridProperty(_T("图块高度"), (_variant_t)0, _T("单元格图块的高度"));
//	pProp->AllowEdit(FALSE);
//	pGroup1->AddSubItem(pProp);
//
//	//添加地图信息属性组
//	m_wndPropList.AddProperty(pGroup1);
//	
//	//图层属性组
//	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("图层"));
//	
//	pProp = new CMFCPropertyGridProperty(_T("当前图层"), _T(""), _T("指定地图当前所编辑的图层。"));
//	pProp->AddOption(_T("地面层"));
//	pProp->AddOption(_T("对象层"));
//	pProp->AddOption(_T("障碍层"));
//	pProp->AddOption(_T("事件层"));
//	pProp->AllowEdit(FALSE);
//	pGroup2->AddSubItem(pProp);
//	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("是否可见"), (_variant_t)false, _T("指定当前图层是否可见，true可见，false隐藏。")));
//	m_wndPropList.AddProperty(pGroup2);
//
//	//触发器属性组
//	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("触发器"));
//	
//	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("触发器ID"), _T(""), _T("每个触发器都有一个ID值，通过ID值获取触发器。")));
//	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("地图ID"), _T(""), _T("指定触发器所指向的地图ID。")));
//	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("起始X位置"),_T(""), _T("指定场景切换后，角色出现的初始X坐标位置。")));
//	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("起始Y位置"), _T(""), _T("指定场景切换后，角色出现的初始Y坐标位置。")));
//	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("角色方向"), _T(""), _T("指定场景切换后，角色的朝向方向，0~8分别表示8个方向。")));
//	m_wndPropList.AddProperty(pGroup3);
//
//	m_wndPropList.ExpandAll(false);
//}
//
//void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
//{
//	CDockablePane::OnSetFocus(pOldWnd);
//	m_wndPropList.SetFocus();
//}
//
//void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
//{
//	CDockablePane::OnSettingChange(uFlags, lpszSection);
//	SetPropListFont();
//}
//
//void CPropertiesWnd::SetPropListFont()
//{
//	::DeleteObject(m_fntPropList.Detach());
//
//	LOGFONT lf;
//	afxGlobalData.fontRegular.GetLogFont(&lf);
//
//	NONCLIENTMETRICS info;
//	info.cbSize = sizeof(info);
//
//	afxGlobalData.GetNonClientMetrics(info);
//
//	lf.lfHeight = info.lfMenuFont.lfHeight;
//	lf.lfWeight = info.lfMenuFont.lfWeight;
//	lf.lfItalic = info.lfMenuFont.lfItalic;
//
//	m_fntPropList.CreateFontIndirect(&lf);
//
//	m_wndPropList.SetFont(&m_fntPropList);
//
//}
//
//void CPropertiesWnd::SetLayerIndexProp(int iLayerIndex)
//{	
//	CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(1);
//
//	switch (iLayerIndex)
//	{
//	case 0:
//		pProp->GetSubItem(0)->SetValue((_variant_t)_T("地面层"));
//		break;
//	case 1:
//		pProp->GetSubItem(0)->SetValue((_variant_t)_T("对象层"));
//		break;
//	case 2:
//		pProp->GetSubItem(0)->SetValue((_variant_t)_T("障碍层"));
//		break;
//	case 3:
//		pProp->GetSubItem(0)->SetValue((_variant_t)_T("事件层"));
//		break;
//	}
//}
//
//bool CPropertiesWnd::GetTriggerProp(CTrigger& trigger)
//{
//
//	CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(2);
//	COleVariant var;
//	
//	var =pProp->GetSubItem(0)->GetValue();
//	if(var == (_variant_t)_T(""))
//	{
//		MessageBox(_T("请设置触发器的ID值"),_T("提示"));
//		ShowPane(true,false,true);
//		ExpandPropGroup(2);
//		return false;
//	}
//	else
//	{
//		var.ChangeType(VT_I4);
//		trigger.SetTriggerID(var.intVal);
//	}
//
//	var = pProp->GetSubItem(1)->GetValue();
//	if(var == (_variant_t)_T(""))
//	{
//		MessageBox(_T("请设置触发器指向的地图ID"),_T("提示"));
//		ShowPane(true,false,true);
//		ExpandPropGroup(2);
//		return false;
//	}
//	else
//	{
//		var.ChangeType(VT_I4);
//		trigger.SetMapID(var.intVal);
//	}
//	var =pProp->GetSubItem(2)->GetValue();
//	if(var == (_variant_t)_T(""))
//	{
//		MessageBox(_T("请设置角色起始X位置"),_T("提示"));
//		ShowPane(true,false,true);
//		ExpandPropGroup(2);
//		return false;
//	}
//	else
//	{
//		var.ChangeType(VT_I4);
//		trigger.SetStartPosX(var.intVal);
//	}
//	var =pProp->GetSubItem(3)->GetValue();
//	if(var == (_variant_t)_T(""))
//	{
//		MessageBox(_T("请设置角色起始Y位置"),_T("提示"));
//		ShowPane(true,false,true);
//		ExpandPropGroup(2);
//		return false;
//	}
//	else
//	{
//		var.ChangeType(VT_I4);
//		trigger.SetStartPosY(var.intVal);
//	}
//
//	var =pProp->GetSubItem(4)->GetValue();
//	if(var == (_variant_t)_T(""))
//	{
//		MessageBox(_T("请设置角色面向方向"),_T("提示"));
//		ShowPane(true,false,true);
//		ExpandPropGroup(2);
//		return false;
//	}
//	else
//	{
//		var.ChangeType(VT_I4);
//		trigger.SetDirection(var.intVal);
//	}
//	ClearTriggerProp();
//	return true;
//}
//
//void CPropertiesWnd::ClearTriggerProp()
//{
//	CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(2);
//	for(int i=0;i<5;i++)
//		pProp->GetSubItem(i)->SetValue(_T(""));
//}
//
//
//
//LRESULT CPropertiesWnd::OnPropertyChanged(WPARAM,LPARAM lParam)
//{
//	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam; 
//
//	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
//	CMapEditorDoc* pDoc = (CMapEditorDoc*)pFrame->GetActiveDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return 0;
//	
//	CMFCPropertyGridProperty* pProp1= m_wndPropList.GetProperty(0);
//	COleVariant var;
//	var = pProp1->GetSubItem(2)->GetValue();
//	var.ChangeType(VT_I4);
//	int orgTileWidth = var.intVal;
//
//	var = pProp1->GetSubItem(3)->GetValue();
//	var.ChangeType(VT_I4);
//	int orgTileHeight = var.intVal;
//
//	var = pProp1->GetSubItem(4)->GetValue();
//	var.ChangeType(VT_I4);
//	int orgOffsetX = var.intVal;
//
//	var = pProp1->GetSubItem(5)->GetValue();
//	var.ChangeType(VT_I4);
//	int orgOffsetY = var.intVal;
//
//	var = pProp->GetValue(); //获取改变之后的值  
//
//	CString strName = pProp->GetName();
//	
////	pDoc->UpdateAllViews(NULL);
//	return 0; 
//}



int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	//创建属性网格
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();
	
	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}
void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top , rectClient.Width(), rectClient.Height() , SWP_NOACTIVATE | SWP_NOZORDER);
}



void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	
	//地图属性组
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("地图属性"));
	//地图宽和高为只读属性，在创建地图时指定，之后不可更改
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("地图宽度"), (_variant_t)0, _T("地图横向单元格个数"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("地图高度"), (_variant_t)0, _T("地图纵向单元格个数"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("图块宽度"), (_variant_t)0, _T("单元格图块的宽度"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("图块高度"), (_variant_t)0, _T("单元格图块的高度"));
	pProp->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp);

	//添加地图信息属性组
	m_wndPropList.AddProperty(pGroup1);
	
	//图层属性组
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("图层"));
	
	pProp = new CMFCPropertyGridProperty(_T("当前图层"), _T(""), _T("指定地图当前所编辑的图层。"));
	pProp->AddOption(_T("地面层"));
	pProp->AddOption(_T("对象层"));
	pProp->AddOption(_T("障碍层"));
	pProp->AddOption(_T("事件层"));
	pProp->AllowEdit(FALSE);
	pGroup2->AddSubItem(pProp);
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("是否可见"), (_variant_t)false, _T("指定当前图层是否可见，true可见，false隐藏。")));
	m_wndPropList.AddProperty(pGroup2);

	//触发器属性组
	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("触发器"));
	
	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("触发器ID"), _T(""), _T("每个触发器都有一个ID值，通过ID值获取触发器。")));
	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("地图ID"), _T(""), _T("指定触发器所指向的地图ID。")));
	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("起始X位置"),_T(""), _T("指定场景切换后，角色出现的初始X坐标位置。")));
	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("起始Y位置"), _T(""), _T("指定场景切换后，角色出现的初始Y坐标位置。")));
	pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("角色方向"), _T(""), _T("指定场景切换后，角色的朝向方向，0~8分别表示8个方向。")));
	m_wndPropList.AddProperty(pGroup3);

	m_wndPropList.ExpandAll(false);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);

}

void CPropertiesWnd::SetLayerIndexProp(int iLayerIndex)
{	
	CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(1);

	switch (iLayerIndex)
	{
	case 0:
		pProp->GetSubItem(0)->SetValue((_variant_t)_T("地面层"));
		break;
	case 1:
		pProp->GetSubItem(0)->SetValue((_variant_t)_T("对象层"));
		break;
	case 2:
		pProp->GetSubItem(0)->SetValue((_variant_t)_T("障碍层"));
		break;
	case 3:
		pProp->GetSubItem(0)->SetValue((_variant_t)_T("事件层"));
		break;
	}
}

bool CPropertiesWnd::GetTriggerProp(CTrigger& trigger)
{

	CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(2);
	COleVariant var;
	
	var =pProp->GetSubItem(0)->GetValue();
	if(var == (_variant_t)_T(""))
	{
		MessageBox(_T("请设置触发器的ID值"),_T("提示"));
		ShowPane(true,false,true);
		ExpandPropGroup(2);
		return false;
	}
	else
	{
		var.ChangeType(VT_I4);
		trigger.SetTriggerID(var.intVal);
	}

	var = pProp->GetSubItem(1)->GetValue();
	if(var == (_variant_t)_T(""))
	{
		MessageBox(_T("请设置触发器指向的地图ID"),_T("提示"));
		ShowPane(true,false,true);
		ExpandPropGroup(2);
		return false;
	}
	else
	{
		var.ChangeType(VT_I4);
		trigger.SetMapID(var.intVal);
	}
	var =pProp->GetSubItem(2)->GetValue();
	if(var == (_variant_t)_T(""))
	{
		MessageBox(_T("请设置角色起始X位置"),_T("提示"));
		ShowPane(true,false,true);
		ExpandPropGroup(2);
		return false;
	}
	else
	{
		var.ChangeType(VT_I4);
		trigger.SetStartPosX(var.intVal);
	}
	var =pProp->GetSubItem(3)->GetValue();
	if(var == (_variant_t)_T(""))
	{
		MessageBox(_T("请设置角色起始Y位置"),_T("提示"));
		ShowPane(true,false,true);
		ExpandPropGroup(2);
		return false;
	}
	else
	{
		var.ChangeType(VT_I4);
		trigger.SetStartPosY(var.intVal);
	}

	var =pProp->GetSubItem(4)->GetValue();
	if(var == (_variant_t)_T(""))
	{
		MessageBox(_T("请设置角色面向方向"),_T("提示"));
		ShowPane(true,false,true);
		ExpandPropGroup(2);
		return false;
	}
	else
	{
		var.ChangeType(VT_I4);
		trigger.SetDirection(var.intVal);
	}
	ClearTriggerProp();
	return true;
}

void CPropertiesWnd::ClearTriggerProp()
{
	CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(2);
	for(int i=0;i<5;i++)
		pProp->GetSubItem(i)->SetValue(_T(""));
}



LRESULT CPropertiesWnd::OnPropertyChanged(WPARAM,LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam; 

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapEditorDoc* pDoc = (CMapEditorDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 0;
	//预留接口函数
//	pDoc->UpdateAllViews(NULL);
	return 0; 
}