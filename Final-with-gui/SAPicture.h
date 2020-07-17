#pragma once


// SAPicture 对话框

class SAPicture : public CDialogEx
{
	DECLARE_DYNAMIC(SAPicture)

public:
	SAPicture(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SAPicture();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SA_PICTURE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMenu m_menu;
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CStatic m_Paint;
	void SADrawYaxis(CDC* Dc, CRect &rectPicture, CPen* pPen);
	void SADrawXaxis(CDC* Dc, CRect &rectPicture, CPen* pPen, double Max);
	void SADrawCurve(CDC* Dc, CRect& rectPicture, CPen* pPen, double* x, double* y, int size, double Max);
	afx_msg void OnSavePicture();
	afx_msg void OnSaveData();
	afx_msg void OnUpdataPicture();
};
