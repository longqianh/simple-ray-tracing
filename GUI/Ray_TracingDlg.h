
// Ray_TracingDlg.h: 头文件
//

#pragma once

// CRayTracingDlg 对话框
class CRayTracingDlg : public CDialogEx
{
// 构造
public:
	CRayTracingDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RAY_TRACING_DIALOG };
#endif
	CMenu m_menu;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void CRayTracingDlg::CreateList1();
	void CRayTracingDlg::CreateList2();
	void CRayTracingDlg::CreateList3();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAbout();  //菜单栏按键
	afx_msg void OnOpenCamFactorFile();
	afx_msg void OnSaveResult();
	CBrush m_brush; //用于改变字体
	CFont m_font;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOpenObjectFactorFile();
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_ACCESSList; //用于创建LIST
	CListCtrl m_ACCESSList2;
	CListCtrl m_ACCESSList3;
	CMFCMaskedEdit* pCurEdit;  //用于单元格编辑
	CMFCMaskedEdit m_Edit_Value;
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit m_Edit;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit m_Edit2;
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnLvnEndlabeleditList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSaveCamFactor();
	afx_msg void OnSaveObjectFactor();
	afx_msg void OnCopyCell();
	afx_msg void OnPasteCell();
	afx_msg void OnInsertFrontSurface();
	afx_msg void OnInsertBackSurface();
	afx_msg void OnDeleteSurface();
	void ResetOrder();
};
