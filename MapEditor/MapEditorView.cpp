
// MapEditorView.cpp : CMapEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MapEditor.h"
#endif

#include "MapEditorDoc.h"
#include "MapEditorView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMapEditorView

IMPLEMENT_DYNCREATE(CMapEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CMapEditorView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CMapEditorView 构造/析构

CMapEditorView::CMapEditorView()
{
	// TODO: 在此处添加构造代码
	m_bLButtonDown=false;
	m_Offset.SetSize(0,0);
}

CMapEditorView::~CMapEditorView()
{
}

BOOL CMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CScrollView::PreCreateWindow(cs);
}

void CMapEditorView::OnInitialUpdate()
{
	CMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CScrollView::OnInitialUpdate();
	
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	//创建一个矩形裁剪区
	
	OnResetMemDC();     

}

// CMapEditorView 绘制

void CMapEditorView::OnDraw(CDC* pDC)
{
	CMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	GetCursorPos(&m_CurPt);
	ScreenToClient(&m_CurPt);
	CRect	rectClient;
	GetClientRect(rectClient);
	CPoint ptScroll = GetScrollPosition();
	
	m_ClipRgn.SetRectRgn(rectClient);
	m_MemDC.SelectClipRgn(&m_ClipRgn);  
	m_MemDC.FillSolidRect(rectClient,RGB(128,128, 128));

	rectClient.OffsetRect(ptScroll);
	m_CurPt.Offset(ptScroll);
	pDoc->m_Map.Draw(&m_MemDC );
	pDoc->m_Map.SetOffSet(-ptScroll.x, -ptScroll.y);
	
	pDoc->DrawDrugImage(&m_MemDC,m_CurPt.x-ptScroll.x,m_CurPt.y-ptScroll.y);
	pDC->BitBlt(rectClient.left,rectClient.top, rectClient.Width(), rectClient.Height(),&m_MemDC,0, 0,SRCCOPY);

}

void CMapEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMapEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_LAYER,point.x,point.y,this,TRUE);
#endif
	
}


// CMapEditorView 诊断

#ifdef _DEBUG
void CMapEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapEditorDoc* CMapEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorDoc)));
	return (CMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditorView 消息处理程序

void CMapEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLButtonDown=true;

	if(pDoc->m_bChose)
		{	//移动物体
			pDoc->m_CurSelObj = pDoc->m_Map.GetObjectLayer().GetCurIndex(point);
		/*	if(pDoc->m_CurSelObj!=-1)
			{
				POINT  pt = pDoc->m_Map.GetObjectLayer().GetObjSet().at(pDoc->m_CurSelObj).GetPos();
				CPoint OldPt =  MapToView(pt.x,pt.y);
				m_Offset = point - OldPt;
			}	*/	
		}
	if(!::IsEmpty()&&pDoc->m_bBrush)
	{
		switch (pDoc->m_iLayerIndex)
		{
		case 0:
			AddTile(point.x,point.y);
			break;
		case 1:
			AddObject(point.x,point.y);
			break;
		case 2:
			AddBlock(point.x,point.y);
			break;
		case 3:
			AddTrigger(point.x,point.y);
			break;
		default:
			break;
		}
		
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMapEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_CurPt = point;
	static CSceneObj* pObj = NULL;
	//仅当鼠标按下时才绘制
	if(m_bLButtonDown)
	{
		if(pDoc->m_bChose)
		{	//移动物体
			pObj = pDoc->m_Map.GetObjectLayer().GetCurChose(m_CurPt);
		/*	if(pObj)
			{
				pObj->SetViewPos(m_CurPt.x-m_Offset.cx , m_CurPt.y-m_Offset.cy);	
			}	*/	
		}

		if(!::IsEmpty()&&pDoc->m_bBrush)
		{
			switch (pDoc->m_iLayerIndex)
			{
			case 0:
				AddTile(m_CurPt.x,m_CurPt.y);
				break;
			case 2:
				AddBlock(m_CurPt.x,m_CurPt.y);
				break;
			default:
				break;
			}
		}
			
	}
	if(pDoc->m_iLayerIndex!=-1)
		Invalidate(false);
	CScrollView::OnMouseMove(nFlags, point);
}

void CMapEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLButtonDown = false;
	CScrollView::OnLButtonUp(nFlags, point);
}

BOOL CMapEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
}
//在屏幕上（x,y）位置贴地板
void CMapEditorView::AddTile(int x,int y)
{
	CMapEditorDoc* pDoc = GetDocument();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSceneResWnd* pSceneWnd = pFrame->GetSceneResWnd();
	int index = pSceneWnd->GetCurSelTileIndex();

	if(index!=-1)
	{
		if(pDoc->m_bEraser)
			pDoc->m_Map.GetTileLayer().DelTile(x,y);
		else
			pDoc->m_Map.GetTileLayer().AddTile(index,x,y);
		pDoc->SetModifiedFlag();
	
		Invalidate(false);//强制调用OnDraw函数
	}		

}

//在屏幕上（x,y）位置贴物体
void CMapEditorView::AddObject(int x,int y)
{
	CMapEditorDoc* pDoc = GetDocument();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSceneResWnd* pSceneWnd = pFrame->GetSceneResWnd();
	
	int iTab = pSceneWnd->GetCurSetTab();
	if(iTab==1)
	{
		int	index = pSceneWnd->GetCurSelObjectIndex();	
		if(index!=-1)
		{
			if(!pDoc->m_bEraser)	
			{

				CSceneObj obj;
				POINT  Pos =  ViewToMap(x,y);
				if(Pos.x>=0&&Pos.x<g_MapWidth&&Pos.y>=0&&Pos.y<g_MapHeight )	
				{
					obj.Create(index,Pos.x,Pos.y);

					pDoc->m_Map.GetObjectLayer().AddObject(obj);
					pDoc->SetModifiedFlag();
					Invalidate(false);//强制调用OnDraw函数
				}
			}
		}		
	}
	else if(iTab==2)
	{
		int	index = pSceneWnd->GetCurSelSpriteIndex();	
		if(index!=-1)
		{
			if(!pDoc->m_bEraser)	
				pDoc->m_Map.GetObjectLayer().AddMonster(index,x,y);
			pDoc->SetModifiedFlag();
			Invalidate(false);//强制调用OnDraw函数
		}	
	}
	
}
//在屏幕上（x,y）位置贴碰撞块
void CMapEditorView::AddBlock(int x,int y)
{
	CMapEditorDoc* pDoc = GetDocument();
	if (!pDoc)
		return;

	//判断是否有地图创建或加载
	
	POINT  pt;
	pt= ViewToGrid(x,y);
	int width = g_MapWidth*(g_TileWidth/g_GridWidth);
	int height = g_MapHeight*(g_TileHeight/g_GridHeight);
	if(pt.x>=0&&pt.x<width&&pt.y>=0&&pt.y<height)
	{	//设为false表示不可通行，即为障碍物
		if(pDoc->m_bEraser)
			pDoc->m_Map.GetBlockLayer().SetPassable(pt.x,pt.y,true);
		else
			pDoc->m_Map.GetBlockLayer().SetPassable(pt.x,pt.y,false);
		pDoc->SetModifiedFlag();
		Invalidate(false);//强制调用OnDraw函数
	}
	
}
//在屏幕上(x,y)位置贴触发器标记
void CMapEditorView::AddTrigger(int x,int y)
{
	CMapEditorDoc* pDoc = GetDocument();
	if (!pDoc)
		return;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CPropertiesWnd* pPropWnd = pFrame->GetPropWnd();
		

	POINT  pt;
	pt= ViewToGrid(x,y);
	int width = g_MapWidth*(g_TileWidth/g_GridWidth);
	int height = g_MapHeight*(g_TileHeight/g_GridHeight);
	if(pt.x>=0&&pt.x<width&&pt.y>=0&&pt.y<height)
	{
		if(pDoc->m_bEraser)
		{
			pDoc->m_Map.GetEventLayer().DelTrigger(pt.x,pt.y);
		}
		else
		{
			CTrigger trigger;
			//触发器属性需要在属性栏指定
			if(!pPropWnd->GetTriggerProp(trigger))
				return;
			trigger.SetPosX(pt.x);
			trigger.SetPosY(pt.y);
			pDoc->m_Map.GetEventLayer().AddTrigger(trigger);
		}
		pDoc->SetModifiedFlag();
		Invalidate(false);//强制调用OnDraw函数
	}
		
}


void CMapEditorView::OnDestroy()
{
	CScrollView::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	m_MemDC.DeleteDC();         //删除DC
	m_MemBmp.DeleteObject();  


	KillTimer(ID_TIMER_SCENE);
}


void CMapEditorView::OnResetMemDC(void)
{
	CMapEditorDoc* pDoc = GetDocument();
	if (!pDoc)
		return;

	//地图包围矩形尺寸
	CSize size=pDoc->m_Map.GetBoundSize();
	SetScrollSizes(MM_TEXT,size);

	CRect rect;
	GetClientRect(&rect);

	int nWidth = rect.Width();
	int nHeight = rect.Height();

	m_MemDC.DeleteDC();
	m_MemBmp.DeleteObject();
	CDC *pDC = GetDC();
	m_MemDC.CreateCompatibleDC(pDC);               //依附窗口DC创建兼容内存DC
	m_MemBmp.CreateCompatibleBitmap(pDC,nWidth,nHeight);//创建兼容位图
	m_MemDC.SelectObject(&m_MemBmp);   
	
	ReleaseDC(pDC);
}


void CMapEditorView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码

	OnResetMemDC();
}


void CMapEditorView::OnTimer(UINT_PTR nIDEvent)
{
	CMapEditorDoc* pDoc = GetDocument();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!::IsEmpty())
	{
		pDoc->m_Map.Update(1.0f/20.0f);
		Invalidate(false);
	}
	CScrollView::OnTimer(nIDEvent);
}


int CMapEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(ID_TIMER_SCENE,40,NULL);
	CRect rect;
	rect.SetRectEmpty();
	m_ClipRgn.CreateRectRgnIndirect(rect);
	return 0;
}


BOOL CMapEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CMapEditorDoc* pDoc = GetDocument();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static float scale = 1.0;
	if(pDoc->m_bChose)
	{
		scale = scale+zDelta/120*0.1f;
		if(scale<=0.25)
			scale = 0.25;
		if(scale>=2.5)
			scale = 2.5;
		if(pDoc->m_CurSelObj!=-1)
		{
			pDoc->m_Map.GetObjectLayer().GetObjSet().at(pDoc->m_CurSelObj).SetScale(scale);
			Invalidate(false);
			return TRUE;
		}
		
	}
	Invalidate(false);
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}
