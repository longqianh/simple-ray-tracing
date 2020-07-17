// ComfirmObjOpen.cpp: 实现文件
//

#include "pch.h"
#include "Ray_Tracing.h"
#include "ComfirmObjOpen.h"
#include "afxdialogex.h"
#include "Ray_TracingDlg.h"
extern std::string** StoreList;
// ComfirmObjOpen 对话框

IMPLEMENT_DYNAMIC(ComfirmObjOpen, CDialogEx)

ComfirmObjOpen::ComfirmObjOpen(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMFIRM_OBJECT_OPEN, pParent)
{

}

ComfirmObjOpen::~ComfirmObjOpen()
{
}

void ComfirmObjOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ComfirmObjOpen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMFIRM_OBJ, &ComfirmObjOpen::OnBnClickedButtonComfirmObj)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_OBJ, &ComfirmObjOpen::OnBnClickedButtonCancelObj)
END_MESSAGE_MAP()


// ComfirmObjOpen 消息处理程序


void ComfirmObjOpen::OnBnClickedButtonComfirmObj()
{
	// TODO: 在此添加控件通知处理程序代码
	CRayTracingDlg* dlg = (CRayTracingDlg*)GetParent();// 
	(*dlg).ListCorrectZero((*dlg).m_ACCESSList3);
	PostMessage(WM_CLOSE, 0, 0);

}


void ComfirmObjOpen::OnBnClickedButtonCancelObj()
{
	// TODO: 在此添加控件通知处理程序代码
	CRayTracingDlg* dlg = (CRayTracingDlg*)GetParent();// 
	if (StoreList != NULL)
	{
		int nltem = atoi(StoreList[0][0].c_str());
		int nlsub = atoi(StoreList[0][1].c_str());
		(*dlg).CreateList3(nlsub);
		int v, j;
		for (v = 1; v < nltem + 1; v++)
			for (j = 0; j < nlsub; j++)
			{
				_bstr_t bstr(StoreList[v][j].c_str());
				(*dlg).m_ACCESSList3.SetItemText(v - 1, j, (LPTSTR)bstr);
			}
		for (int i = 0; i < nltem + 1; i++)
			delete[]StoreList[i];
		delete StoreList;
	}
	else
		while ((*dlg).m_ACCESSList3.DeleteItem(0));
	(*dlg).ResetOrder();
	PostMessage(WM_CLOSE, 0, 0);
}
