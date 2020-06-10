
#pragma once

#include "EventLayer.h"

//属性停靠窗口
class CPropertiesWnd : public CDockablePane
{
// 构造
public:
	CPropertiesWnd();

	void AdjustLayout();

// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}
	//设定显示地图大小信息
	void SetMapSizeProp(int width,int height)
	{	
		CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(0);
		pProp->GetSubItem(0)->SetValue((_variant_t)width);
		pProp->GetSubItem(1)->SetValue((_variant_t)height);
	}
	//设定显示瓷砖大小信息
	void SetTileSizeProp(int width,int height)
	{	
		CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(0);
		pProp->GetSubItem(2)->SetValue((_variant_t)width);
		pProp->GetSubItem(3)->SetValue((_variant_t)height);
	}
	
	//设定显示图层信息
	void SetLayerIndexProp(int iLayerIndex);
	//显示图层信息
	void SetLayerVisibleProp(bool bVisible)
	{
		CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(1);
		pProp->GetSubItem(1)->SetValue((_variant_t)bVisible);
	}
	//获取触发器属性
	bool GetTriggerProp(CTrigger& trigger);
	//展开第nIndex属性组
	void ExpandPropGroup(int nIndex)
	{
		CMFCPropertyGridProperty* pProp= m_wndPropList.GetProperty(nIndex);
		m_wndPropList.ExpandAll(false);
		pProp->Expand();
		SetFocus();
	}
private:
	//清空触发器属性
	void ClearTriggerProp();

protected:
	CFont			   m_fntPropList;
	//属性格控件
	CMFCPropertyGridCtrl m_wndPropList;

// 实现
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//属性改变事件处理
	afx_msg LRESULT OnPropertyChanged(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
	//初始化属性列表
	void InitPropList();
	void SetPropListFont();
};


