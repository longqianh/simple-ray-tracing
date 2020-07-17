// SAPicture.cpp: 实现文件
//

#include "pch.h"
#include "Ray_Tracing.h"
#include "SAPicture.h"
#include "afxdialogex.h"
#include "apifuncs.h"
#include "Ray_TracingDlg.h"

#define INTERVAL 0.01
//全局变量声明
extern BOOL SAPicture_only_exit_one_flag;
extern OptSys sys;
extern double* nds;
extern double* ncs;
extern double l;
extern double y_or_W;

// SAPicture 对话框
IMPLEMENT_DYNAMIC(SAPicture, CDialogEx)

SAPicture::SAPicture(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SA_PICTURE, pParent)
{

}

SAPicture::~SAPicture()
{
}

void SAPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRAW_SA_BG, m_Paint);
}


BEGIN_MESSAGE_MAP(SAPicture, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_SAVE_PICTURE, &SAPicture::OnSavePicture)
	ON_COMMAND(ID_SAVE_DATA, &SAPicture::OnSaveData)
	ON_COMMAND(ID_UPDATA_PICTURE, &SAPicture::OnUpdataPicture)
END_MESSAGE_MAP()


// SAPicture 消息处理程序


void SAPicture::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SAPicture_only_exit_one_flag = 0;
	CDialogEx::OnClose();
}


int SAPicture::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// 将菜单项添加到系统菜单中。
	m_menu.LoadMenuW(IDR_MENU5); //IDR_MENU5是菜单资源ID
	SetMenu(&m_menu); //将菜单加入到对话框。
	return 0;
}


void SAPicture::OnPaint()
{
	CPaintDC dc(this);
	CDC* Dc = m_Paint.GetDC(); // device context for painting
	
	// TODO: 在此处添加消息处理程序代码
	
	double* SA = nullptr;
	double interval = INTERVAL;
	int size = 1.0 / interval+1; //额外加上0这个点
	double* y = new double[size];
	for (int i = 0; i < size; i++)
		y[i] = INTERVAL * i;
	
	//调用函数得到球差值
	SA = get_SAs(sys, l, interval);

	//绘图
	//横坐标 左右 0-最大的SA[size-1]
	//纵坐标0-1 视场 每0.1一格
	CPen*  pBlack_wide = new CPen();
	CPen* pBlue = new CPen();
	CPen* pWhite = new CPen();
	pBlack_wide->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pBlue->CreatePen(PS_SOLID, 2, RGB(142, 229, 238));
	pWhite->CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	CRect rectPicture;
	Dc->SelectObject(pWhite);   //选择白笔刷
	m_Paint.GetClientRect(&rectPicture);   //选择picturecontrol 变量m_Paint
	Dc->Rectangle(rectPicture);  //将背景图成白色

	SADrawYaxis(Dc, rectPicture, pBlack_wide);
	SADrawXaxis(Dc, rectPicture, pBlack_wide, abs(SA[size - 1]));
	SADrawCurve(Dc, rectPicture, pBlue, SA, y, size, abs(SA[size - 1]));

	delete[] y;
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

void SAPicture::SADrawYaxis(CDC * Dc, CRect  &rectPicture, CPen * pPen)
{
	//0.1一格
	Dc->SelectObject(pPen);
	//画点Dc->SetPixel(x, y, color);
	int XLength = rectPicture.right - rectPicture.left;
	int YLength = rectPicture.bottom - rectPicture.top;
	int XCenter = (rectPicture.right - rectPicture.left) / 2;
	int YCenter = (rectPicture.bottom - rectPicture.top) / 2;
	
	Dc->MoveTo(XCenter, rectPicture.top); 
	Dc->LineTo(XCenter, YLength * 22 / 25); //预留4/25高给底端文字 1/25高给顶端
	
	int LineInterval = YLength * 4 / 5 / 10;
	int YaxisLength = 10 * LineInterval;
	int i;
	for (i = 0; i < 10; i++)
	{
		Dc->MoveTo(XCenter - XLength / 50, YLength * 22 / 25 - (i + 1) * LineInterval);
		Dc->LineTo(XCenter + XLength / 50, YLength * 22 / 25 - (i + 1) * LineInterval);
	}

	POINT Triangle[3] = { {XCenter, rectPicture.top},{XCenter * 41 / 40, YLength / 40},{XLength / 2 * 39 / 40,YLength / 40} };
	Dc->SelectObject(GetStockObject(DC_BRUSH));  
	Dc->SelectObject(GetStockObject(DC_PEN));
	Dc->SetDCPenColor(RGB(0, 0, 0)); //pen是边框
	Dc->SetDCBrushColor(RGB(0, 0, 0));	//brush是填充颜色
	Dc->Polygon(Triangle, 3);

	CFont font;
	int CharacterHeight = 20;
	font.CreateFont(CharacterHeight,                                    //   字体的高度   
		0,                                          //   字体的宽度  
		0,                                          //  nEscapement 
		0,                                          //  nOrientation   
		FW_NORMAL,                                  //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                                   //   cStrikeOut   
		ANSI_CHARSET,                             //   nCharSet   
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		DEFAULT_QUALITY,                       //   nQuality   
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("宋体"));
	Dc->SelectObject(&font);
	Dc->SetBkMode(TRANSPARENT);
	Dc->SetTextColor(RGB(0, 0, 0));
	CString Graduation[10] = { L"0.1",L"0.2",L"0.3",L"0.4",L"0.5",L"0.6",L"0.7",L"0.8",L"0.9",L"1.0" };
	for (i = 0; i < 10; i++)
		Dc->TextOutW(XCenter + XLength / 25, YLength * 22 / 25 - (i + 1) * LineInterval - CharacterHeight / 2, Graduation[i]);
	Dc->TextOutW(XCenter + XLength / 25, rectPicture.top, L"归一化孔径");
}

void SAPicture::SADrawXaxis(CDC* Dc, CRect &rectPicture, CPen* pPen, double Max)
{
	Dc->SelectObject(pPen);
	//画点Dc->SetPixel(x, y, color);
	int XLength = rectPicture.right - rectPicture.left;
	int YLength = rectPicture.bottom - rectPicture.top;
	int XCenter = (rectPicture.right - rectPicture.left) / 2;
	int YCenter = (rectPicture.bottom - rectPicture.top) / 2;
	
	//Max = 1.0000001; //测试11.00000001这个数值
	Dc->MoveTo(rectPicture.left, YLength * 22 / 25);
	Dc->LineTo(rectPicture.right, YLength * 22 / 25); //预留4/25高给底端文字 1/25高给顶端
	CRayTracingDlg* dlg = (CRayTracingDlg*)GetParent();// 
	string max = (*dlg).DoubleToString(Max, 16);
	_bstr_t maxpositive(max.c_str());
	_bstr_t maxnegative(("-"+max).c_str());
	int StrLength = max.size();

	 CFont font;
	 int CharacterHeight = 20;
	 int CharacterWeight = 10;
	 font.CreateFont(CharacterHeight,                                    //   字体的高度   
		 CharacterWeight,                                          //   字体的宽度  
		 0,                                          //  nEscapement 
		 0,                                          //  nOrientation   
		 FW_NORMAL,                                  //   nWeight   
		 FALSE,                                      //   bItalic   
		 FALSE,                                      //   bUnderline   
		 0,                                                   //   cStrikeOut   
		 ANSI_CHARSET,                             //   nCharSet   
		 OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		 CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		 DEFAULT_QUALITY,                       //   nQuality   
		 DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		 _T("宋体"));
	 Dc->SelectObject(&font);
	 Dc->SetBkMode(TRANSPARENT);
	 Dc->SetTextColor(RGB(0, 0, 0));
	 Dc->TextOutW(XCenter - CharacterWeight / 2, YLength * 22 / 25, L"0");
	 if (Max != 0)
	 {
		 Dc->TextOutW(rectPicture.right - (StrLength + 1) * CharacterWeight, YLength * 22 / 25, (LPTSTR)maxpositive);
		 Dc->TextOutW(rectPicture.left, YLength * 22 / 25, (LPTSTR)maxnegative);
	 }
	 
}

void SAPicture::SADrawCurve(CDC* Dc, CRect& rectPicture, CPen* pPen, double* x, double* y, int size, double Max)
{
	Dc->SelectObject(pPen);
	//画点Dc->SetPixel(x, y, color);
	int XLength = rectPicture.right - rectPicture.left;
	int YLength = rectPicture.bottom - rectPicture.top;
	int XCenter = (rectPicture.right - rectPicture.left) / 2;
	int YCenter = (rectPicture.bottom - rectPicture.top) / 2;
	int YaxisLength = YLength * 4 / 5;
	double YPointInterval = 1.0 / YaxisLength;
	int YStart = YLength * 22 / 25;
	double XPointInterval = 2.0 * Max / XLength;

	int i;
	int XPosition, YPosition;
	Dc->MoveTo(XCenter, YStart);
	for (i = 1; i < size; i++)
	{
		if (XPointInterval == 0)
			XPosition = XCenter;
		else if (x[i] <= 0)
			XPosition = XCenter - abs(x[i]) / XPointInterval;
		else
			XPosition = XCenter + abs(x[i]) / XPointInterval;
		YPosition = YStart - y[i] / YPointInterval;
		Dc->LineTo(XPosition, YPosition);
	}

}

void SAPicture::OnSavePicture()
{
	// TODO: 在此添加命令处理程序代码
	/*CWnd* bmpShow = GetDlgItem(IDC_DRAW_SA_BG);*/ // 直接根据ID选择
	CDC* pdc = m_Paint.GetDC();
	CImage  imag;
	CRect rect;
	m_Paint.GetClientRect(&rect);
	//GetClientRect(&rect);        //获取画布大小
	//bmpShow->GetWindowRect(&rect);
	imag.Create(rect.Width(), rect.Height() - 20, 32);
	::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);

	TCHAR szFilter[] = _T("jpg file(*.jpg)|*.jpg|bmp file(*.bmp)|*.bmp|所有文件(*.*)|*.*||");  //文件格式过滤
	// 构造保存文件对话框    
	CFileDialog fileDlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	fileDlg.m_ofn.lpstrTitle = _T("球差曲线图");  //保存对话窗口标题名
	CString picturePath;
	if (IDOK == fileDlg.DoModal())  //按下确认键
	{
		picturePath = fileDlg.GetPathName();  //文件路径
	}

	HRESULT hResult = imag.Save(picturePath); //保存图片
	ReleaseDC(pdc);
	imag.ReleaseDC();
}


void SAPicture::OnSaveData()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isOpen = FALSE;        //是否打开(否则为保存)  
	CString defaultDir = L"E:\\FileTest";   //默认打开的文件路径  
	CString fileName = L"球差曲线图数据.csv";         //默认打开的文件名  
	CString filter = L"文件  (*.txt*.csv)|*.txt;*.csv||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\球差曲线图数据.csv";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + L"\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		AfxMessageBox(L"保存成功！");
	}
	ofstream outFile;
	outFile.open(filePath, ios::out);
	outFile << "横轴球差" << ',' << "纵轴归一化孔径" << endl;
	
	int size = 1 / INTERVAL + 1;
	double* y = new double[size];
	for (int i = 0; i < size; i++)
		y[i] = INTERVAL * i;
	//调用函数得到球差值
	double* Data;
	Data = get_SAs(sys, l, INTERVAL);
	int v, j;
	for (v = 0; v < size; v++)
		for (j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				CRayTracingDlg* dlg = (CRayTracingDlg*)GetParent();// 
				string str = (*dlg).DoubleToString(Data[v], 16);
				_bstr_t bstr(str.c_str());
				outFile << CT2A(bstr) << ',';
			}
			else
			{
				CRayTracingDlg* dlg = (CRayTracingDlg*)GetParent();// 
				string str = (*dlg).DoubleToString(y[v], 16);
				_bstr_t bstr(str.c_str());
				outFile << CT2A(bstr) << endl;
			}
		}
	outFile.close();
}


void SAPicture::OnUpdataPicture()
{
	// TODO: 在此添加命令处理程序代码
	Invalidate(); //更新
}
