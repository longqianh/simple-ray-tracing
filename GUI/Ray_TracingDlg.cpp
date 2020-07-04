
// Ray_TracingDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Ray_Tracing.h"
#include "Ray_TracingDlg.h"
#include "afxdialogex.h"
#include "aboutdlg.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRayTracingDlg 对话框

int m_Row, m_Col;

CRayTracingDlg::CRayTracingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RAY_TRACING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CRayTracingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ACCESSList);
	//DDX_Control(pDX, IDC_EDIT1, editcontrol);
	//DDX_Control(pDX, IDC_EDIT2, tablenameedit);
	DDX_Control(pDX, IDC_LIST2, m_ACCESSList2);
	DDX_Control(pDX, IDC_LIST3, m_ACCESSList3);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
}

BEGIN_MESSAGE_MAP(CRayTracingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ABOUT, &CRayTracingDlg::OnAbout)
	ON_COMMAND(ID_OPEN_CAM_FACTOR_FILE, &CRayTracingDlg::OnOpenCamFactorFile)
	ON_COMMAND(ID_SAVE_RESULT, &CRayTracingDlg::OnSaveResult)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CRayTracingDlg::OnLvnItemchangedList1)
	ON_COMMAND(ID_OPEN_OBJECT_FACTOR_FILE, &CRayTracingDlg::OnOpenObjectFactorFile)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CRayTracingDlg::OnLvnItemchangedList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CRayTracingDlg::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CRayTracingDlg::OnEnKillfocusEdit1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CRayTracingDlg::OnLvnItemchangedList3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &CRayTracingDlg::OnNMDblclkList3)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CRayTracingDlg::OnEnKillfocusEdit2)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST3, &CRayTracingDlg::OnLvnEndlabeleditList3)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CRayTracingDlg::OnNMRClickList1)
	ON_COMMAND(ID_SAVE_CAM_FACTOR, &CRayTracingDlg::OnSaveCamFactor)
	ON_COMMAND(ID_SAVE_OBJECT_FACTOR, &CRayTracingDlg::OnSaveObjectFactor)
	ON_COMMAND(ID_COPY_CELL, &CRayTracingDlg::OnCopyCell)
	ON_COMMAND(ID_PASTE_CELL, &CRayTracingDlg::OnPasteCell)
	ON_COMMAND(ID_INSERT_FRONT_SURFACE, &CRayTracingDlg::OnInsertFrontSurface)
	ON_COMMAND(ID_INSERT_BACK_SURFACE, &CRayTracingDlg::OnInsertBackSurface)
	ON_COMMAND(ID_DELETE_SURFACE, &CRayTracingDlg::OnDeleteSurface)
END_MESSAGE_MAP()


// CRayTracingDlg 消息处理程序

BOOL CRayTracingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_font.CreatePointFont(150, L"微软雅黑");
	m_brush.CreateSolidBrush(RGB(0, 255, 0));
	
	// 将菜单项添加到系统菜单中。
	m_menu.LoadMenuW(IDR_MENU1); //IDR_MENU1是菜单资源ID
	SetMenu(&m_menu); //将菜单加入到对话框。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//隐藏
	m_Edit.ShowWindow(SW_HIDE);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CreateList1();
	CreateList2();
	CreateList3();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRayTracingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRayTracingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRayTracingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRayTracingDlg::OnAbout()
{
	aboutdlg dlg;
	dlg.DoModal();
}

void CRayTracingDlg::OnOpenCamFactorFile()
{
	BOOL isOpen = TRUE;     //是否打开(否则为保存)  
	CString defaultDir = L"E:\\FileTest";   //默认打开的文件路径  
	CString fileName = L"";         //默认打开的文件名  
	CString filter = L"文件 (*.txt*.csv)|*.txt;*.csv||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";
	INT_PTR result = openFileDlg.DoModal();
	// CString filePath = defaultDir + L"\\test.doc"; 
	CString filePath;
	if (result==IDOK) {
		filePath = openFileDlg.GetPathName();
		AfxMessageBox(L"读取成功！");
	}
	//CWnd::SetDlgItemTextW(IDC_EDIT1, filePath);
	ifstream inFile(filePath, ios::in);
	string lineStr;
	vector<vector<string>> strArray;
	while (getline(inFile, lineStr))
	{
		// 打印整行字符串
		cout << lineStr << endl;
		// 存成二维表结构
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		// 按照逗号分隔
		while (getline(ss, str, ',')) //ss为得到的数据  得到的数据进行后处理传递给算法不过首先得先列表列出来
		lineArray.push_back(str);
		strArray.push_back(lineArray);
	}
	//清除
	while (m_ACCESSList.DeleteItem(0));
	int v, j,start_row,start_col,temp;
	LPTSTR str;
	string x;
	if (strArray[0][0] == "序号")   //兼容两种格式，包含表头的一种格式(正式格式，也是输出格式)，不包含表头的也不包含序号的(草稿格式)
	{
		start_row = 1;
		start_col = 1;
	}
	else
	{
		start_row = 0;
		start_col = 0;
	}
	for(v=0;v<(strArray.size()- start_row);v++)
	{
		temp = min(strArray[v].size()-start_row+1, 6);
		for (j = 0; j < temp; j++)
		{
			LV_ITEM lvitemAdd = { 0 };
			lvitemAdd.mask = LVIF_TEXT;
			lvitemAdd.iItem = v; //行
			lvitemAdd.iSubItem = j;//列
			if (j == 0) 
			{
				x = to_string(v+1);
				_bstr_t bstr(x.c_str());
				str = (LPTSTR)bstr;
				lvitemAdd.pszText = str;
				m_ACCESSList.InsertItem(&lvitemAdd);//插入行
			}
			else 
			{
				_bstr_t bstr(strArray[v+start_row][j-1+start_col].c_str());
				str = (LPTSTR)bstr;
				lvitemAdd.pszText = str;
			}
			m_ACCESSList.SetItem(&lvitemAdd); //插入数据	
		}
	}
}


void CRayTracingDlg::OnSaveResult()
{
	BOOL isOpen = FALSE;        //是否打开(否则为保存)  
	CString defaultDir = L"E:\\FileTest";   //默认打开的文件路径  
	CString fileName = L"计算结果.csv";         //默认打开的文件名  
	CString filter = L"文件  (*.txt*.csv)|*.txt;*.csv||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\计算结果.csv";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + L"\\" + fileName;
	if (result==IDOK) {
		filePath = openFileDlg.GetPathName();
		AfxMessageBox(L"保存成功！");
	}
	ofstream outFile;
	outFile.open(filePath, ios::out);
	outFile << "计算参数" << ',' << "数值结果" << endl;
	int v, j;
	int nltem = m_ACCESSList2.GetItemCount();
	if(nltem != 0)
	{
		for (v=0;v<nltem;v++)
			for (j = 0; j < 2; j++)
			{
				if (j != 1)
					outFile << CT2A(m_ACCESSList.GetItemText(v, j).GetString()) << ',';
				else
					outFile << CT2A(m_ACCESSList.GetItemText(v, j).GetString()) << endl;
			}	
	}
	outFile.close();
	// TODO: 在此添加命令处理程序代码
}
HBRUSH CRayTracingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));//文字为黑色
		pDC->SelectObject(&m_font);//文字为15号字体，华文行楷
		return m_brush;
	}
	return hbr;
}


void CRayTracingDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CRayTracingDlg::OnOpenObjectFactorFile()
{
	
	BOOL isOpen = TRUE;     //是否打开(否则为保存)  
	CString defaultDir = L"E:\\FileTest";   //默认打开的文件路径  
	CString fileName = L"";         //默认打开的文件名  
	CString filter = L"文件 (*.txt*.csv)|*.txt;*.csv||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";
	INT_PTR result = openFileDlg.DoModal();
	// CString filePath = defaultDir + L"\\test.doc"; 
	CString filePath;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		AfxMessageBox(L"读取成功！");
	}
	//CWnd::SetDlgItemTextW(IDC_EDIT1, filePath);
	ifstream inFile(filePath, ios::in);
	string lineStr;
	vector<vector<string>> strArray;
	while (getline(inFile, lineStr))
	{
		// 打印整行字符串
		cout << lineStr << endl;
		// 存成二维表结构
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		// 按照逗号分隔
		while (getline(ss, str, ',')) //ss为得到的数据  得到的数据进行后处理传递给算法不过首先得先列表列出来
			lineArray.push_back(str);
		strArray.push_back(lineArray);
	}
	//清除
	while (m_ACCESSList3.DeleteItem(0));
	int v, j,temp,start_row;
	LPTSTR str;
	LV_ITEM lvitemAdd = { 0 };
	lvitemAdd.mask = LVIF_TEXT;
	lvitemAdd.iItem = 0; //行
	lvitemAdd.iSubItem =0;//列
	lvitemAdd.pszText = L"";
	m_ACCESSList3.InsertItem(&lvitemAdd);//插入行
	if (strArray[0][0] == "物方距离")   //兼容两种格式，包含表头的一种格式(正式格式，也是输出格式)，不包含表头的也不包含序号的(草稿格式)
		start_row = 1;
	else
		start_row = 0;
	for (v = 0; v < strArray.size()-start_row; v++)
	{
		temp = min(strArray[v].size(), 4);
		for (j = 0; j < temp; j++)
		{
			lvitemAdd.iItem = v; //行
			lvitemAdd.iSubItem = j;//列
			_bstr_t bstr(strArray[v+start_row][j].c_str());
			str = (LPTSTR)bstr;
			lvitemAdd.pszText = str;
			m_ACCESSList3.SetItem(&lvitemAdd); //插入数据	
		}
	}
	// TODO: 在此添加命令处理程序代码
}


void CRayTracingDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

// 设置镜头参数的表
void CRayTracingDlg::CreateList1()
{
	//清除
	while (m_ACCESSList.DeleteItem(0));
	while (m_ACCESSList.DeleteColumn(0));
	//设置List
	DWORD dwStyle = ::GetWindowLong(m_ACCESSList.m_hWnd, GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);
	SetWindowLong(m_ACCESSList.m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);
	DWORD styles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(m_ACCESSList.m_hWnd, styles, styles);
	//设置列头
	LV_COLUMN lvcolumn;
	CRect rect;
	m_ACCESSList.GetWindowRect(&rect);
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_ORDER;
	lvcolumn.fmt = LVCFMT_CENTER;
	//设置行高
	CImageList imagelist;
	imagelist.Create(1, 30, ILC_COLOR, 1, 1);
	m_ACCESSList.SetImageList(&imagelist, LVSIL_SMALL);
	TCHAR fieldname[7][10] = { _T(""),_T("序号"),  _T("曲率半径"), _T("厚度"), _T("d光折射率") , _T("F光折射率") , _T("C光折射率") };
	for (int i = 0; i < 7; i++)
	{
		lvcolumn.pszText = fieldname[i];
		lvcolumn.iSubItem = i;
		lvcolumn.iOrder = i;
		//曲率半径 厚度 三个n 
		if (i == 0)
			lvcolumn.cx = 0;
		if (i == 1)
			lvcolumn.cx = rect.Width() / 21;
		else
			lvcolumn.cx = rect.Width() * 4 / 21;
		m_ACCESSList.InsertColumn(i, &lvcolumn);
	}
	m_ACCESSList.DeleteColumn(0);
}

void CRayTracingDlg::CreateList2()
{
	//设置计算结果的表
		//清除
	while (m_ACCESSList2.DeleteItem(0));
	while (m_ACCESSList2.DeleteColumn(0));
	//设置List
	DWORD dwStyle = ::GetWindowLong(m_ACCESSList2.m_hWnd, GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);
	SetWindowLong(m_ACCESSList2.m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);
	DWORD styles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(m_ACCESSList2.m_hWnd, styles, styles);
	//设置列头
	LV_COLUMN lvcolumn;
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_ORDER;
	lvcolumn.fmt = LVCFMT_CENTER;
	//设置行高
	CImageList imagelist;
	imagelist.Create(1, 30, ILC_COLOR, 1, 1);
	m_ACCESSList2.SetImageList(&imagelist, LVSIL_SMALL);
	CRect rect;
	m_ACCESSList2.GetWindowRect(&rect);
	TCHAR fieldname2[3][30] = { _T(""),  _T("计算参数"),  _T("数值结果") };
	for (int i = 0; i < 3; i++)
	{
		lvcolumn.pszText = fieldname2[i];
		lvcolumn.iSubItem = i;
		lvcolumn.iOrder = i;
		//曲率半径 厚度 三个n 
		if (i == 0)
		lvcolumn.cx = 0;
		else
			lvcolumn.cx = rect.Width() / 2;
		m_ACCESSList2.InsertColumn(i, &lvcolumn);
	}
	m_ACCESSList2.DeleteColumn(0);
}

void CRayTracingDlg::CreateList3()
{
	//设置计算结果的表
		//清除
	while (m_ACCESSList3.DeleteItem(0));
	while (m_ACCESSList3.DeleteColumn(0));
	//设置List
	DWORD dwStyle = ::GetWindowLong(m_ACCESSList3.m_hWnd, GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);
	SetWindowLong(m_ACCESSList3.m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT | LVS_NOLABELWRAP | LVS_SHOWSELALWAYS);
	DWORD styles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(m_ACCESSList3.m_hWnd, styles, styles);
	//设置列头
	LV_COLUMN lvcolumn;
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_ORDER;
	lvcolumn.fmt = LVCFMT_CENTER;
	CRect rect;
	m_ACCESSList3.GetWindowRect(&rect);
	//设置行高
	CImageList imagelist;
	imagelist.Create(1, 30, ILC_COLOR, 1, 1);
	m_ACCESSList3.SetImageList(&imagelist, LVSIL_SMALL);
	//物方参数 距离 无穷远时视场角W 有限距离是半孔径角U 物高y
	TCHAR fieldname3[5][40] = { _T(""), _T("物方距离"),  _T("无穷远半视场角W"),_T("有限距离半孔径角U"),  _T("物高y") };
	for (int i = 0; i < 5; i++)
	{
		lvcolumn.pszText = fieldname3[i];
		lvcolumn.iSubItem = i;
		lvcolumn.iOrder = i;
		//曲率半径 厚度 三个n 
		if(i==0)
			lvcolumn.cx = 0;
		else
			lvcolumn.cx = rect.Width() / 4;
		m_ACCESSList3.InsertColumn(i, &lvcolumn);
	}
	m_ACCESSList3.DeleteColumn(0);
}

void CRayTracingDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列
	if (pNMListView->iItem != -1) //如果选择的是子项;
	{
		m_ACCESSList.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；
		m_Edit.SetParent(&m_ACCESSList);//转换坐标为列表框中的坐标
		m_Edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_Edit.SetWindowText(m_ACCESSList.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；
		m_Edit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_Edit.SetFocus();//设置Edit焦点
		m_Edit.ShowCaret();//显示光标
		m_Edit.SetSel(-1);//将光标移动到最后
	}
	*pResult = 0;
}

void CRayTracingDlg::OnEnKillfocusEdit1()
{
	CString tem;
	m_Edit.GetWindowText(tem);    //得到用户输入的新的内容
	m_ACCESSList.SetItemText(m_Row, m_Col, tem);   //设置编辑框的新内容
	m_Edit.ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


void CRayTracingDlg::OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CRayTracingDlg::OnNMDblclkList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列
	if (pNMListView->iItem != -1) //如果选择的是子项;
	{
		m_ACCESSList3.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；
		m_Edit2.SetParent(&m_ACCESSList3);//转换坐标为列表框中的坐标
		m_Edit2.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_Edit2.SetWindowText(m_ACCESSList3.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；
		m_Edit2.ShowWindow(SW_SHOW);//显示Edit控件；
		m_Edit2.SetFocus();//设置Edit焦点
		m_Edit2.ShowCaret();//显示光标
		m_Edit2.SetSel(-1);//将光标移动到最后
	}
	/*POSITION pos = m_ACCESSList3.GetFirstSelectedItemPosition();
	int nIndex = m_ACCESSList3.GetNextSelectedItem(pos);
	if (nIndex >= 0)
	{
		m_ACCESSList3.SetFocus();
		CEdit* pEdit = m_ACCESSList3.EditLabel(nIndex);
	}*/
	*pResult = 0;
}


void CRayTracingDlg::OnEnKillfocusEdit2()
{
	CString tem;
	m_Edit2.GetWindowText(tem);    //得到用户输入的新的内容
	m_ACCESSList3.SetItemText(m_Row, m_Col, tem);   //设置编辑框的新内容
	m_Edit2.ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


void CRayTracingDlg::OnLvnEndlabeleditList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//CString strName = pDispInfo->item.pszText;
	//int nIndex = pDispInfo->item.iItem;
	//m_ACCESSList3.SetFocus();
	//if ((!strName.IsEmpty()) && nIndex >= 0)
	//{
	//	m_ACCESSList3.SetItemText(nIndex, 0, strName);
	//}
	*pResult = 0;
}


void CRayTracingDlg::OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列
	if (pNMListView->iItem != -1)
	{
		POINT pt;
		GetCursorPos(&pt);
		int x = m_ACCESSList.GetSelectionMark();
		CMenu menu;
		menu.LoadMenuW(IDR_MENU2);
		CMenu* pop = menu.GetSubMenu(0);
		pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
		*pResult = 0;
	}
	else
	{
		POINT pt;
		GetCursorPos(&pt);
		int x = m_ACCESSList.GetSelectionMark();
		CMenu menu;
		menu.LoadMenuW(IDR_MENU3);
		CMenu* pop = menu.GetSubMenu(0);
		pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
		*pResult = 0;
	}
}


void CRayTracingDlg::OnSaveCamFactor()
{
	BOOL isOpen = FALSE;        //是否打开(否则为保存)  
	CString defaultDir = L"E:\\FileTest";   //默认打开的文件路径  
	CString fileName = L"镜头参数.csv";         //默认打开的文件名  
	CString filter = L"文件  (*.txt*.csv)|*.txt;*.csv||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\镜头参数.csv";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + L"\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		AfxMessageBox(L"保存成功！");
	}
	ofstream outFile;
	outFile.open(filePath, ios::out);
	outFile << "序号" << ',' << "曲率半径" << ',' << "厚度" << ',' << "d光折射率" << ',' << "F光折射率" << ',' << "C光折射率" << endl;
	int v, j;
	int nltem = m_ACCESSList.GetItemCount();
	if (nltem != 0)
	{
		for (v = 0; v < nltem; v++)
			for (j = 0; j < 6; j++)
			{
				if (j != 5)
					outFile << CT2A(m_ACCESSList.GetItemText(v, j).GetString())<< ',';
				else
					outFile << CT2A(m_ACCESSList.GetItemText(v, j).GetString()) << endl;
			}
	}
	outFile.close();
	// TODO: 在此添加命令处理程序代码
}


void CRayTracingDlg::OnSaveObjectFactor()
{
	BOOL isOpen = FALSE;        //是否打开(否则为保存)  
	CString defaultDir = L"E:\\FileTest";   //默认打开的文件路径  
	CString fileName = L"物方参数.csv";         //默认打开的文件名  
	CString filter = L"文件  (*.txt*.csv)|*.txt;*.csv||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\物方参数.csv";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + L"\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		AfxMessageBox(L"保存成功！");
	}
	ofstream outFile;
	outFile.open(filePath, ios::out);
	outFile << "物方距离" << ',' << "无穷远半视场角W" << ',' << "有限距离半孔径角U" << ',' << "物高y" << endl;
	int v, j;
	int nltem = m_ACCESSList3.GetItemCount();
	if (nltem != 0)
	{
		for (v = 0; v < nltem; v++)
			for (j = 0; j < 4; j++)
			{
				if (j != 3)
					outFile << CT2A(m_ACCESSList3.GetItemText(v, j).GetString()) << ',';
				else
					outFile << CT2A(m_ACCESSList3.GetItemText(v, j).GetString()) << endl;
			}
	}
	outFile.close();
	// TODO: 在此添加命令处理程序代码
}


void CRayTracingDlg::OnCopyCell()
{
	//复制剪切板
	if (!m_ACCESSList.GetItemText(m_Row, m_Col).IsEmpty())
	{
		if (OpenClipboard())
		{
			EmptyClipboard(); //清空剪贴板，使该窗口成为剪贴板的拥有者
			HGLOBAL hClip;
			hClip = GlobalAlloc(GMEM_MOVEABLE, (m_ACCESSList.GetItemText(m_Row, m_Col).GetLength() * 2) + 2); //判断要是文本数据，分配内存时多分配一个字符
			TCHAR* pBuf;
			pBuf = (TCHAR*)GlobalLock(hClip);//锁定剪贴板
			lstrcpy(pBuf, m_ACCESSList.GetItemText(m_Row, m_Col));//把CString转换
			GlobalUnlock(hClip);//解除锁定剪贴板
			SetClipboardData(CF_TEXT, hClip);//把文本数据发送到剪贴板 CF_UNICODETEXT为Unicode编码
		}
		CloseClipboard();
	}
	// TODO: 在此添加命令处理程序代码
}


void CRayTracingDlg::OnPasteCell()
{
	//粘贴
	char* buffer = NULL; 
	CString   fromClipboard;
	if (OpenClipboard())
	{
		HANDLE   hData = GetClipboardData(CF_TEXT);
		char* buffer = (char*)GlobalLock(hData);
		fromClipboard = buffer;
		GlobalUnlock(hData);
		CloseClipboard();
	}
	m_ACCESSList.SetItemText(m_Row, m_Col, fromClipboard);
	// TODO: 在此添加命令处理程序代码
}

void CRayTracingDlg::ResetOrder()
{
	int nltem = m_ACCESSList.GetItemCount();
	int v;
	string x;
	for (v = 0; v < nltem; v++)
	{
		x = to_string(v + 1);
		_bstr_t bstr(x.c_str());
		m_ACCESSList.SetItemText(v, 0, (LPTSTR)bstr );
	}
}

void CRayTracingDlg::OnInsertFrontSurface()
{
	LV_ITEM lvitemAdd = { 0 };
	lvitemAdd.mask = LVIF_TEXT;
	lvitemAdd.iItem = m_Row; //行
	lvitemAdd.iSubItem = m_Col;//列
	lvitemAdd.pszText = L"";
	m_ACCESSList.InsertItem(&lvitemAdd);//插入行
	// TODO: 在此添加命令处理程序代码
}


void CRayTracingDlg::OnInsertBackSurface()
{
	// TODO: 在此添加命令处理程序代码
}


void CRayTracingDlg::OnDeleteSurface()
{
	// TODO: 在此添加命令处理程序代码
}
