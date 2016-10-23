// Search.cpp : 实现文件
//

#include "stdafx.h"
#include "Graph.h"
#include "2.h"
#include "2Doc.h"
#include "2View.h"
#include "Search.h"
#include "afxdialogex.h"

#define WM_SENDMESSAGE WM_USER+101 
// CSearch 对话框

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


// CSearch 消息处理程序

BOOL CSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Start.InsertString(0, _T("三食堂"));
	Start.InsertString(1, _T("大学生活动中心"));
	Start.InsertString(2, _T("弘毅堂"));
	Start.InsertString(3, _T("教三"));
	Start.InsertString(4, _T("教一楼"));
	Start.InsertString(5, _T("主楼"));
	Start.InsertString(6, _T("52栋"));
	Start.InsertString(7, _T("物探楼"));
	Start.InsertString(8, _T("开水房"));
	Start.InsertString(9, _T("数理楼"));

	End.InsertString(0, _T("三食堂"));
	End.InsertString(1, _T("大学生活动中心"));
	End.InsertString(2, _T("弘毅堂"));
	End.InsertString(3, _T("教三"));
	End.InsertString(4, _T("教一楼"));
	End.InsertString(5, _T("主楼"));
	End.InsertString(6, _T("52栋"));
	End.InsertString(7, _T("物探楼"));
	End.InsertString(8, _T("开水房"));
	End.InsertString(9, _T("数理楼"));
	return TRUE;
}


void CSearch::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	OnCancel();
}


void CSearch::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (Start.GetCurSel() == End.GetCurSel())
	{
		MessageBox(_T("起点终点为同一个地点"), _T("错误"), MB_OK);
		return;
	}
	int start = Start.GetCurSel();
	int end = End.GetCurSel();
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_SENDMESSAGE, start, end);
	OnOK();
}
