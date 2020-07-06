// ComfirmCamOpen.cpp: 实现文件
//

#include "pch.h"
#include "Ray_Tracing.h"
#include "ComfirmCamOpen.h"
#include "afxdialogex.h"
#include "Ray_TracingDlg.h"

extern std::string** StoreList;
// ComfirmCamOpen 对话框
//extern CRayTracingDlg* pCRayTracingDlg;
IMPLEMENT_DYNAMIC(ComfirmCamOpen, CDialogEx)

ComfirmCamOpen::ComfirmCamOpen(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMFIRM_CAM_OPEN, pParent)
{

}

ComfirmCamOpen::~ComfirmCamOpen()
{
}

void ComfirmCamOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ComfirmCamOpen, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_COMFIRM_CAM, &ComfirmCamOpen::OnBnClickedButtonComfirmCam)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_CAM, &ComfirmCamOpen::OnBnClickedButtonCancelCam)
END_MESSAGE_MAP()


// ComfirmCamOpen 消息处理程序


void ComfirmCamOpen::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}


void ComfirmCamOpen::OnBnClickedButtonComfirmCam()
{
	// TODO: 在此添加控件通知处理程序代码
	CRayTracingDlg* dlg = (CRayTracingDlg*)GetParent();// 
	(*dlg).ListCorrectZero((*dlg).m_ACCESSList);
	PostMessage(WM_CLOSE, 0, 0);
}


void ComfirmCamOpen::OnBnClickedButtonCancelCam()
{
	// TODO: 在此添加控件通知处理程序代码
	CRayTracingDlg* dlg = (CRayTracingDlg*)GetParent();// 
	if (StoreList != NULL)
	{
		int nltem = atoi(StoreList[0][0].c_str());
		int nlsub = atoi(StoreList[0][1].c_str());
		(*dlg).CreateList1();
		int v, j;
		for (v = 1; v < nltem + 1; v++)
			for (j = 0; j < nlsub; j++)
			{
				_bstr_t bstr(StoreList[v][j].c_str());
				(*dlg).m_ACCESSList.SetItemText(v - 1, j, (LPTSTR)bstr);
			}
		for (int i = 0; i < nltem+1; i++)
		delete[]StoreList[i];
		delete StoreList;
		while ((*dlg).m_ACCESSList.DeleteItem(nltem));
	}
	else
		while ((*dlg).m_ACCESSList.DeleteItem(0));
	(*dlg).ResetOrder();
	PostMessage(WM_CLOSE, 0, 0);
}
