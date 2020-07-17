#include "pch.h"
#include "ButtonTransparent.h"


void ButtonTransparent::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC = pDC->SaveDC();//�洢��ǰ�豸�������Ա��ͼ����ʱ�ָ�ԭ��״̬</span>
	pDC->SelectObject(&m_normalBrush);//ѡ��ť����״̬��Ĭ��״̬���µĻ�ˢ
	pDC->SelectObject(&m_Pen);//ѡ�񻭱�
	CRect rct = lpDrawItemStruct->rcItem;//��ȡ��ť��������
	if (lpDrawItemStruct->itemState & ODS_SELECTED)//���ư�ť����ʱ����ɫ
	{
		pDC->SelectObject(&m_activeBrush);
	}
	pDC->Ellipse(&rct);//����Բ��ť����һ������֮ǰѡ��Ļ��ʺͻ�ˢ

	//�ػ�����
	pDC->SetBkMode(TRANSPARENT);//�ػ��ı�ʱ������������͸��ģʽ�����ѡ��OPAQUE����͸���������ı������а�ɫ���α߿�ʮ��֮�ѿ�
	CString strText{};//c++11�汾���²�֧�ִ˷���
	GetWindowText(strText);//��ȡ��ť�ı�
	pDC->DrawText(strText, rct, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ػ水ť�ı�

	//�ָ��豸����
	pDC->RestoreDC(nSaveDC);

	// TODO:  ������Ĵ����Ի���ָ����
}


//BOOL ButtonTransparent::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	return CButton::PreTranslateMessage(pMsg);
//}


void ButtonTransparent::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	ModifyStyle(0, BS_OWNERDRAW);//��Ϊ�Ի���

	// ���ư�ť���������е��ĸ��߽�
	CRgn rgn;
	CRect rct;
	GetClientRect(&rct);
	rgn.CreateEllipticRgnIndirect(&rct);//�ڰ�ť�����ڴ�����Բ����
	::SetWindowRgn(GetSafeHwnd(), (HRGN)rgn, true);//����Բ����Ӧ�õ���ť��
	CButton::PreSubclassWindow();

	CButton::PreSubclassWindow();
}
ButtonTransparent::ButtonTransparent()
{
	m_Pen.CreatePen(PS_SOLID, 1, RGB(201, 201, 233));
	m_normalBrush.CreateSolidBrush(RGB(231, 221, 223));//����״̬�µİ�ť��ɫ
	m_activeBrush.CreateSolidBrush(RGB(201, 201, 233));//��ť����ʱ�İ�ť��ɫ

}
ButtonTransparent::~ButtonTransparent()
{
	m_Pen.DeleteObject();
	m_normalBrush.DeleteObject();
	m_activeBrush.DeleteObject();
}