// Search.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Graph.h"
#include "2.h"
#include "2Doc.h"
#include "2View.h"
#include "Search.h"
#include "afxdialogex.h"

#define WM_SENDMESSAGE WM_USER+101 
// CSearch �Ի���

IMPLEMENT_DYNAMIC(CSearch, CDialogEx)

CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearch::IDD, pParent)
{

}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Start);
	DDX_Control(pDX, IDC_COMBO2, End);
}


BEGIN_MESSAGE_MAP(CSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CSearch::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CSearch::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSearch ��Ϣ�������

BOOL CSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Start.InsertString(0, _T("��ʳ��"));
	Start.InsertString(1, _T("��ѧ�������"));
	Start.InsertString(2, _T("������"));
	Start.InsertString(3, _T("����"));
	Start.InsertString(4, _T("��һ¥"));
	Start.InsertString(5, _T("��¥"));
	Start.InsertString(6, _T("52��"));
	Start.InsertString(7, _T("��̽¥"));
	Start.InsertString(8, _T("��ˮ��"));
	Start.InsertString(9, _T("����¥"));

	End.InsertString(0, _T("��ʳ��"));
	End.InsertString(1, _T("��ѧ�������"));
	End.InsertString(2, _T("������"));
	End.InsertString(3, _T("����"));
	End.InsertString(4, _T("��һ¥"));
	End.InsertString(5, _T("��¥"));
	End.InsertString(6, _T("52��"));
	End.InsertString(7, _T("��̽¥"));
	End.InsertString(8, _T("��ˮ��"));
	End.InsertString(9, _T("����¥"));
	return TRUE;
}


void CSearch::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void CSearch::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (Start.GetCurSel() == End.GetCurSel())
	{
		MessageBox(_T("����յ�Ϊͬһ���ص�"), _T("����"), MB_OK);
		return;
	}
	int start = Start.GetCurSel();
	int end = End.GetCurSel();
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_SENDMESSAGE, start, end);
	OnOK();
}
