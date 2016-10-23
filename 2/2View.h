
// 2View.h : CMy2View 类的接口
//

#pragma once
#include "Graph.h"
#include "2Doc.h"

struct Info
{
	bool tag;	//true为经典，false为拐点
	int x;
	int y;
	bool operator == (Info& j)
	{
		return ((j.x == x) && (j.y == y));
	}
};

class CMy2View : public CScrollView
{
protected: // 仅从序列化创建
	CMy2View();
	DECLARE_DYNCREATE(CMy2View);

// 特性
public:
	CMy2Doc* GetDocument() const;

// 操作
public:
	GraphLink<Info, int> MyMap;
	CToolTipCtrl m_Info;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT ReceiveMessage2(WPARAM wParam, LPARAM lParam);
};



#ifndef _DEBUG  // 2View.cpp 中的调试版本
inline CMy2Doc* CMy2View::GetDocument() const
   { return reinterpret_cast<CMy2Doc*>(m_pDocument); }
#endif

