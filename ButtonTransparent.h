#pragma once
#include <afxwin.h>
class ButtonTransparent :
	public CButton
{
public:
	ButtonTransparent();
	~ButtonTransparent();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	CBrush m_normalBrush;
	CPen m_Pen;
	CBrush m_activeBrush;
};

