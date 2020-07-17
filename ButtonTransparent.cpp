#include "pch.h"
#include "ButtonTransparent.h"


void ButtonTransparent::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC = pDC->SaveDC();//存储当前设备环境，以便绘图结束时恢复原来状态</span>
	pDC->SelectObject(&m_normalBrush);//选择按钮正常状态（默认状态）下的画刷
	pDC->SelectObject(&m_Pen);//选择画笔
	CRect rct = lpDrawItemStruct->rcItem;//获取按钮矩形区域
	if (lpDrawItemStruct->itemState & ODS_SELECTED)//绘制按钮按下时的颜色
	{
		pDC->SelectObject(&m_activeBrush);
	}
	pDC->Ellipse(&rct);//画椭圆按钮，这一步用了之前选择的画笔和画刷

	//重绘字体
	pDC->SetBkMode(TRANSPARENT);//重绘文本时不擦除背景即透明模式，如果选择OPAQUE（不透明），在文本四周有白色矩形边框，十分之难看
	CString strText{};//c++11版本以下不支持此方法
	GetWindowText(strText);//获取按钮文本
	pDC->DrawText(strText, rct, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//重绘按钮文本

	//恢复设备环境
	pDC->RestoreDC(nSaveDC);

	// TODO:  添加您的代码以绘制指定项
}


//BOOL ButtonTransparent::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	return CButton::PreTranslateMessage(pMsg);
//}


void ButtonTransparent::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0, BS_OWNERDRAW);//改为自绘风格

	// 绘制按钮可用区域，切掉四个边角
	CRgn rgn;
	CRect rct;
	GetClientRect(&rct);
	rgn.CreateEllipticRgnIndirect(&rct);//在按钮矩形内创建椭圆区域
	::SetWindowRgn(GetSafeHwnd(), (HRGN)rgn, true);//将椭圆区域应用到按钮上
	CButton::PreSubclassWindow();

	CButton::PreSubclassWindow();
}
ButtonTransparent::ButtonTransparent()
{
	m_Pen.CreatePen(PS_SOLID, 1, RGB(201, 201, 233));
	m_normalBrush.CreateSolidBrush(RGB(231, 221, 223));//正常状态下的按钮颜色
	m_activeBrush.CreateSolidBrush(RGB(201, 201, 233));//按钮按下时的按钮颜色

}
ButtonTransparent::~ButtonTransparent()
{
	m_Pen.DeleteObject();
	m_normalBrush.DeleteObject();
	m_activeBrush.DeleteObject();
}