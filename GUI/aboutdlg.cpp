// aboutdlg.cpp: 实现文件
//

#include "pch.h"
#include "Ray_Tracing.h"
#include "aboutdlg.h"
#include "afxdialogex.h"


// aboutdlg 对话框

IMPLEMENT_DYNAMIC(aboutdlg, CDialogEx)

aboutdlg::aboutdlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{

}

aboutdlg::~aboutdlg()
{
}

void aboutdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(aboutdlg, CDialogEx)
	ON_COMMAND(ID_ABOUT, &aboutdlg::OnAbout)
END_MESSAGE_MAP()


// aboutdlg 消息处理程序

void aboutdlg::OnAbout() 
{
	aboutdlg dlg;
	dlg.DoModal();
}