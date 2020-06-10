#pragma once


// CNewMapDlg 对话框

class CNewMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewMapDlg)

public:
	CNewMapDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewMapDlg();

// 对话框数据
	enum { IDD = IDD_NEWMAPDLG };
	int	m_iMapWidth;
	int m_iMapHeight;
	int m_iTileWidth;
	int m_iTileHeight;

	CComboBox m_ctrTileSize;
	CString		m_strSize;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreatemap();
	virtual BOOL OnInitDialog();
};
