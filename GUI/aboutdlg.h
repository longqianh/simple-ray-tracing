#pragma once


// aboutdlg 对话框

class aboutdlg : public CDialogEx
{
	DECLARE_DYNAMIC(aboutdlg)

public:
	aboutdlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~aboutdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAbout();
};
