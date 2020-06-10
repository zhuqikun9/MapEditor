#pragma once

#define IDC_THUMBLIST		80
// CThumbWnd

class CThumbWnd : public CWnd
{
	DECLARE_DYNAMIC(CThumbWnd)

public:
	CThumbWnd();
	virtual ~CThumbWnd();

	CListCtrl	m_ListCtrl;
	CImageList  m_ImageList;
	CSize	    m_ThumbSize;
	//记录当前选中的索引
	int			m_iCurSelItem;
public:
	//初始化缩略图列表,默认缩略图宽和高为64
	void		CreateThumbList(CArray<CTexture>& imageList,int width = 64,int height =64);
	//往缩略图列表里添加一个图片
	void		AddThumb(CTexture& srcImage);

	//获取当前选中的索引
	int			GetCurSelResID(){	return m_iCurSelItem; }

protected:
	void	AdjustLayout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSelectListItem(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


