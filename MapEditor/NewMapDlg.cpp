// NewMapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor.h"
#include "NewMapDlg.h"
#include "afxdialogex.h"


// CNewMapDlg 对话框

IMPLEMENT_DYNAMIC(CNewMapDlg, CDialogEx)

CNewMapDlg::CNewMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewMapDlg::IDD, pParent)
{
	m_iMapWidth=10;
	m_iMapHeight=10;
	m_iTileWidth=64;
	m_iTileHeight=32;
	m_strSize = _T("");
}

CNewMapDlg::~CNewMapDlg()
{
}

void CNewMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_MAPWIDTH,m_iMapWidth);
	DDX_Text(pDX,IDC_MAPHEIGHT,m_iMapHeight);
	DDV_MinMaxInt(pDX,m_iMapWidth,10,100);
	DDV_MinMaxInt(pDX,m_iMapHeight,10,100);

	DDX_Control(pDX,IDC_TILESIZE,m_ctrTileSize);
	DDX_CBString(pDX,IDC_TILESIZE,m_strSize);

}


BEGIN_MESSAGE_MAP(CNewMapDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CREATEMAP, &CNewMapDlg::OnBnClickedCreatemap)
END_MESSAGE_MAP()


// CNewMapDlg 消息处理程序

BOOL CNewMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ctrTileSize.AddString(_T(" 64 X 32"));
	m_ctrTileSize.AddString(_T(" 96 X 48"));
	m_ctrTileSize.AddString(_T("128 X 64"));
	m_ctrTileSize.AddString(_T("160 X 80"));
	m_ctrTileSize.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CNewMapDlg::OnBnClickedCreatemap()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_ctrTileSize.GetCurSel())
	{
	case 0:
		m_iTileWidth = 64;
		m_iTileHeight = 32;
		break;
	case 1:
		m_iTileWidth = 96;
		m_iTileHeight = 48;
		break;
	case 2:
		m_iTileWidth = 128;
		m_iTileHeight = 64;
		break;
	case 3:
		m_iTileWidth = 160;
		m_iTileHeight = 80;
		break;
	default:
		break;
	}
	UpdateData();
	OnOK();
}


