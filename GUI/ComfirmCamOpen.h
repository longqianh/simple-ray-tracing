#pragma once


// ComfirmCamOpen 对话框

class ComfirmCamOpen : public CDialogEx
{
	DECLARE_DYNAMIC(ComfirmCamOpen)

public:
	ComfirmCamOpen(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ComfirmCamOpen();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMFIRM_CAM_OPEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonComfirmCam();
	afx_msg void OnBnClickedButtonCancelCam();
};
