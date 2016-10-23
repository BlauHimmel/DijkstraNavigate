#pragma once
#include "afxwin.h"


// CSearch 对话框

class CSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CSearch)

public:
	CSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearch();
	BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CComboBox Start;
	CComboBox End;
	afx_msg void OnBnClickedButton1();
};
