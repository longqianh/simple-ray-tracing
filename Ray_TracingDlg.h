// Ray_TracingDlg.h: 头文件
//

#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include "framework.h"
#include "Ray_Tracing.h"
#include "afxdialogex.h"
#include "aboutdlg.h"
#include "ComfirmCamOpen.h"
#include "ComfirmObjOpen.h"
#include "ButtonTransparent.h"
#include "SAPicture.h"
#include <fstream>
#include <sstream>
#include <GdiPlus.h>
#include <cassert>
#include "apifuncs.h"

#define INF 1e15

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
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAbout();  //菜单栏按键
	afx_msg void OnOpenCamFactorFile();
	afx_msg void OnSaveResult();
	CMenu m_menu;
	CBrush m_brush; //用于改变字体
	CFont m_font;
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
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
	int Delete = 0;
	afx_msg void OnInsertSurface();
	afx_msg void OnCalculateResult();
	afx_msg void OnBnClickedButtonCalculate();
	afx_msg void OnNMRClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpLine();
	afx_msg void OnDownLine();
	afx_msg void OnNMKillfocusList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMKillfocusList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetInfinity();
	afx_msg void OnSetDistance();
	afx_msg void OnCopyCell2();
	afx_msg void OnPasteCell2();
	afx_msg void OnCopyCell3();
	afx_msg void OnPasteCell3();
	afx_msg void OnQiushiBlue();
	CButton m_Button_Cal;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void RefreshControl(UINT uCtlID);
	afx_msg void OnBgcWhite();
	afx_msg void OnBgcStar();
	afx_msg void OnBgcChageblue();
	afx_msg void OnBgcSlightgreen();
	afx_msg void OnBgcmacaron();
	BOOL JudgeStringIsFloat(std::string x);
	BOOL JudgeListIsCorrect(CListCtrl& m_List);
	void ListCorrectZero(CListCtrl& m_List);
	double TransStrToDouble(std::string x);
	void ZeroDotCorrectFormat(CListCtrl& m_List);
	void StoreLastList(CListCtrl& m_List);
	void CreateList1();
	void CreateList2();
	void CreateList3(int nlsub);
	string DoubleToString(const double value, unsigned int precisionAfterPoint);
	afx_msg void OnDrawSaCurve();
	afx_msg void OnDraw2d();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUserInstruction();
	afx_msg void OnBnClickedMfcbutton1();
	CMFCButton m_mfcbutton;
};
