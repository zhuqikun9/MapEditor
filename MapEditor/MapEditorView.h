
// MapEditorView.h : CMapEditorView 类的接口
//

#pragma once
#define ID_TIMER_SCENE 101//计时器ID



class CMapEditorView : public CScrollView
{
protected: // 仅从序列化创建
	CMapEditorView();
	DECLARE_DYNCREATE(CMapEditorView)

// 特性
public:
	CMapEditorDoc* GetDocument() const;
	//调整内存DC大小
	void	OnResetMemDC(void);
public:
	CDC		m_MemDC;                  //用于缓冲作图的内存DC
	CBitmap m_MemBmp;             //内存中承载临时图象的位图
	bool	m_bLButtonDown;
	//记录鼠标相对整个地图左上角的位置
	CPoint	m_CurPt;
	CSize	m_Offset;
	//裁剪区域
	CRgn	m_ClipRgn;
// 操作
public:

	//在屏幕上(x，y)处贴图块
	void AddTile(int x,int y);
	//在屏幕上（x,y）位置画物体
	void AddObject(int x,int y);
	//在屏幕上(x,y)位置贴障碍块
	void AddBlock(int x,int y);
	//在屏幕上(x,y)位置贴触发器标记
	void AddTrigger(int x,int y);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	
protected:

// 实现
public:
	virtual ~CMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnDestroy();
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // MapEditorView.cpp 中的调试版本
inline CMapEditorDoc* CMapEditorView::GetDocument() const
   { return reinterpret_cast<CMapEditorDoc*>(m_pDocument); }
#endif

