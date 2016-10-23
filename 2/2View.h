
// 2View.h : CMy2View ��Ľӿ�
//

#pragma once
#include "Graph.h"
#include "2Doc.h"

struct Info
{
	bool tag;	//trueΪ���䣬falseΪ�յ�
	int x;
	int y;
	bool operator == (Info& j)
	{
		return ((j.x == x) && (j.y == y));
	}
};

class CMy2View : public CScrollView
{
protected: // �������л�����
	CMy2View();
	DECLARE_DYNCREATE(CMy2View);

// ����
public:
	CMy2Doc* GetDocument() const;

// ����
public:
	GraphLink<Info, int> MyMap;
	CToolTipCtrl m_Info;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT ReceiveMessage2(WPARAM wParam, LPARAM lParam);
};



#ifndef _DEBUG  // 2View.cpp �еĵ��԰汾
inline CMy2Doc* CMy2View::GetDocument() const
   { return reinterpret_cast<CMy2Doc*>(m_pDocument); }
#endif

