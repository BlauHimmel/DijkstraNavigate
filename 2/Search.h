#pragma once
#include "afxwin.h"


// CSearch �Ի���

class CSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CSearch)

public:
	CSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearch();
	BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CComboBox Start;
	CComboBox End;
	afx_msg void OnBnClickedButton1();
};
