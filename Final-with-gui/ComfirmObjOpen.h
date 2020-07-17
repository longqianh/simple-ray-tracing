#pragma once


// ComfirmObjOpen 对话框

class ComfirmObjOpen : public CDialogEx
{
	DECLARE_DYNAMIC(ComfirmObjOpen)

public:
	ComfirmObjOpen(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ComfirmObjOpen();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMFIRM_OBJECT_OPEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonComfirmObj();
	afx_msg void OnBnClickedButtonCancelObj();
};
