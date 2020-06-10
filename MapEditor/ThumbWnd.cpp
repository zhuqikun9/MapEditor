// ThumbWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor.h"
#include "ThumbWnd.h"


// CThumbWnd

IMPLEMENT_DYNAMIC(CThumbWnd, CWnd)

CThumbWnd::CThumbWnd()
{
	m_iCurSelItem = -1;
	m_ThumbSize = CSize(64,64);
}

CThumbWnd::~CThumbWnd()
{
}


BEGIN_MESSAGE_MAP(CThumbWnd, CWnd)
	ON_NOTIFY(NM_CLICK,IDC_THUMBLIST,OnSelectListItem)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CThumbWnd 消息处理程序




int CThumbWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | LVS_ICON;

	if (!m_ListCtrl.Create(dwViewStyle, rectDummy, this, IDC_THUMBLIST))
	{
		TRACE0("未能创建列表\n");
		return -1;      // 未能创建
	}
	m_ListCtrl.SetExtendedStyle(LVS_AUTOARRANGE);
	m_ListCtrl.SetBkColor(RGB(213,228,242));

	AdjustLayout();

	return 0;
}


void CThumbWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AdjustLayout();
}

void CThumbWnd::AdjustLayout()
{
	CRect rectClient;
	GetClientRect(rectClient);
	m_ListCtrl.SetWindowPos(this, rectClient.left , rectClient.top , rectClient.Width() - 1, rectClient.Height() - 1, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ListCtrl.Arrange(LVA_DEFAULT);
}

//更据传入的图片列表，创建对应的缩略图列表
void CThumbWnd::CreateThumbList(CArray<CTexture>& imageList,int width,int height)
{

	m_ThumbSize.SetSize(width,height);
	m_ImageList.DeleteImageList();
	m_ImageList.Create(m_ThumbSize.cx, m_ThumbSize.cy, ILC_COLOR32|ILC_MASK,128,128);
	m_ListCtrl.SetImageList(&m_ImageList, TVSIL_NORMAL );
	for(int i=0;i<imageList.GetSize();i++)
	{
		AddThumb(imageList.GetAt(i));
	}
}
//往缩略图列表里添加一个缩略图
void CThumbWnd::AddThumb(CTexture& srcImage)
{
	//设定缩略图宽度和高度
	int thumbWidth = m_ThumbSize.cx;
	int thumbHeight = min((LONG)srcImage.GetHeight(), m_ThumbSize.cy);                                         

	CClientDC cdc(this);

	CDC MemDC;           //用于缓冲作图的内存DC
	CBitmap MemBmp;      //内存中承载临时图象的位图
	MemDC.CreateCompatibleDC(&cdc);     //依附窗口DC创建兼容内存DC
	MemBmp.CreateCompatibleBitmap(&cdc,thumbWidth,thumbHeight);//创建兼容位图
	MemDC.SelectObject(&MemBmp);       //将位图选择进内存DC
	MemDC.FillSolidRect(CRect(0,0,thumbWidth,thumbHeight),RGB(255,255, 255));//清屏

	srcImage.Draw(&MemDC,0,0,thumbWidth,thumbHeight);   //在内存DC中绘图
	
	CBitmap bmp;
	bmp.Attach(MemBmp.Detach());	
	
	MemDC.DeleteDC();                                       //删除DC
	MemBmp.DeleteObject();

	m_ImageList.Add(&bmp,RGB(255,255,255));
	int nItem = m_ImageList.GetImageCount()-1;

	CString strItem = srcImage.GetFileName();
	int i=strItem.ReverseFind(_T('/'));
	strItem.Delete(0,i+1);
	//插入列表项
	m_ListCtrl.InsertItem(nItem,strItem,nItem);

	bmp.DeleteObject();
}

void CThumbWnd::OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_iCurSelItem = pNMLV->iItem;

	*pResult = 0;
}