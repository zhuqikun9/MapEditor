
// MapEditorDoc.h : CMapEditorDoc 类的接口
//


#pragma once

#include "TileMap.h"
#include "PropertiesWnd.h"




class CMapEditorDoc : public CDocument
{
protected: // 仅从序列化创建
	CMapEditorDoc();
	DECLARE_DYNCREATE(CMapEditorDoc)

// 特性
public:
	CPropertiesWnd* m_pPropWnd;
	
	CTileMap		m_Map;

	//当前编辑的图层索引,0:地面层，1：对象层，2，：障碍层，3：事件层
	int		m_iLayerIndex;

	//橡皮擦除工具标记
	bool	m_bEraser;

	//图层隐藏工具标记
	bool	m_bLayerVisible;
	//选择工具标记
	bool	m_bChose;
	//拖动工具
	bool	m_bDrug;
	//画刷模式标记
	bool	m_bBrush;
	//缩放系数
	float	m_fScale;
	//记录当前活动地图文件路径
	CString	m_strMapFilePath;

	//当前选中物体编号
	int		m_CurSelObj;
// 操作
public:
	//初始化状态
	void	InitStates();
	//通知View重新指定内存DC大小
	void	OnResetMemDC();
	//绘制拖拽图片
	void	DrawDrugImage(CDC *pDC,int destX,int destY);
	////获取与屏幕上某一点对应的地图中的对象的索引
	//int		GetCurChose(CPoint point);
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMapEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnLayerTile();
	afx_msg void OnUpdateLayerTile(CCmdUI *pCmdUI);
	afx_msg void OnLayerObject();
	afx_msg void OnUpdateLayerObject(CCmdUI *pCmdUI);
	afx_msg void OnLayerEvent();
	afx_msg void OnUpdateLayerEvent(CCmdUI *pCmdUI);
	afx_msg void OnLayerVisible();
	afx_msg void OnUpdateLayerVisible(CCmdUI *pCmdUI);
	afx_msg void OnLayerBlock();
	afx_msg void OnUpdateLayerBlock(CCmdUI *pCmdUI);
	afx_msg void OnEditEraser();
	afx_msg void OnUpdateEditEraser(CCmdUI *pCmdUI);
	afx_msg void OnViewShowGrid();
	afx_msg void OnUpdateViewShowGrid(CCmdUI *pCmdUI);
	afx_msg void OnViewZoomin();
	afx_msg void OnUpdateViewZoomin(CCmdUI *pCmdUI);
	afx_msg void OnViewZoomout();
	afx_msg void OnUpdateViewZoomout(CCmdUI *pCmdUI);
	afx_msg void OnViewNormal();
	afx_msg void OnUpdateViewNormal(CCmdUI *pCmdUI);
	afx_msg void OnMapPreview();

	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
	
	afx_msg void OnEditChose();
	afx_msg void OnUpdateEditChose(CCmdUI *pCmdUI);
	afx_msg void OnEditBrush();
	afx_msg void OnUpdateEditBrush(CCmdUI *pCmdUI);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI *pCmdUI);
	afx_msg void OnViewShowrole();
	afx_msg void OnUpdateViewShowrole(CCmdUI *pCmdUI);
	afx_msg void OnAppHelp();
	afx_msg void OnEditFill();
};

