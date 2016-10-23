
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "2.h"
#include "2View.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_SENDMESSAGE WM_USER+101 

#define WM_SENDMESSAGE2 WM_USER+102 
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_SENDMESSAGE, ReceiveMessage)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����


LRESULT CMainFrame::ReceiveMessage(WPARAM wParam, LPARAM lParam)
{
	int start = wParam;
	int end = (int)lParam;
	
	CMainFrame* pmain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMy2View* cview = (CMy2View*)pmain->GetActiveView();

	::SendMessage(cview->m_hWnd, WM_SENDMESSAGE2, start, end);

	return 0;
}

CMainFrame::CMainFrame() 
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetDlgCtrlID(), SBPS_NORMAL, 100);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cx = 1280;
	cs.cy = 660;
	cs.style &= ~WS_THICKFRAME; //ȥ���ɸı��С�ı߿�
	cs.style |= WS_DLGFRAME; //���Ӳ��ܸı��С�ı߿�
	cs.style &= ~FWS_ADDTOTITLE;
	cs.lpszName = _T("У԰����ϵͳ");
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFrameWnd::OnMouseMove(nFlags, point);

	CString str;
	str.Format(_T("X=%d Y=%d"), point.x, point.y);

	m_wndStatusBar.SetPaneText(2, str);
	
}
