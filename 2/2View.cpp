
// 2View.cpp : CMy2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "2.h"
#endif

#include "2Doc.h"
#include "2View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define R 5

#define WM_SENDMESSAGE2 WM_USER+102 

// CMy2View

IMPLEMENT_DYNCREATE(CMy2View, CScrollView)

BEGIN_MESSAGE_MAP(CMy2View, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_SENDMESSAGE2, ReceiveMessage2)
END_MESSAGE_MAP()

BOOL CMy2View::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
		case WM_MOUSEMOVE:
			m_Info.RelayEvent(pMsg);
	}
	return CScrollView::PreTranslateMessage(pMsg);
}

int transfer(int index)		//��combobox�е�indexת��Ϊvertex�е��±�
{
	switch (index)
	{
	case 0:
		return 2;
	case 1:
		return 12;
	case 2:
		return 3;
	case 3:
		return 11;
	case 4:
		return 9;
	case 5:
		return 10;
	case 6:
		return 4;
	case 7:
		return 7;
	case 8:
		return 0;
	case 9:
		return 8;
	default:
		return -1;
	}
}

LRESULT CMy2View::ReceiveMessage2(WPARAM wParam, LPARAM lParam)
{
	RedrawWindow();
	int start = wParam;
	int end = (int)lParam;

	int StartVertexIndex = transfer(start);
	int EndVertexIndex = transfer(end);

	int *path, *distance;	//need delete
	int n = 0, length = 0;

	Info startVertex = MyMap.getValue(StartVertexIndex);
	Info endVertex = MyMap.getValue(EndVertexIndex);

	Dijkstra(MyMap, startVertex, path, distance);
	Info* result;		//need delete
	result = GetDijkstraPath(MyMap, path, distance, startVertex, endVertex, n, length);

	CDC* dc = GetDC();
	CPen pen(PS_SOLID, 4, RGB(255, 0, 0));
	dc->SelectObject(&pen);

	dc->Ellipse(result[0].x - R, result[0].y + R, result[0].x + R, result[0].y - R);
	for (int i = 0; i < n - 1; i++)
	{
		dc->MoveTo(result[i].x, result[i].y);
		dc->LineTo(result[i + 1].x, result[i + 1].y);
	}
	dc->Ellipse(result[n - 1].x - R, result[n - 1].y + R, result[n - 1].x + R, result[n - 1].y - R);

	CString STRdistance;
	STRdistance.Format(_T("%d"), distance[n - 1]);
	STRdistance = _T("����:") + STRdistance + _T("m");

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->m_wndStatusBar.SetPaneText(0, STRdistance);

	delete[] path;
	delete[] distance;
	delete[] result;
	return 0;
}

// CMy2View ����/����
CMy2View::CMy2View()
{
	// TODO:  �ڴ˴���ӹ������

	Info Vertex[17];

	Vertex[2].x = 19;	//ѧ��
	Vertex[2].y = 287;
	Vertex[2].tag = true;

	Vertex[12].x = 110;	//���
	Vertex[12].y = 189;
	Vertex[12].tag = true;

	Vertex[3].x = 93;	//������
	Vertex[3].y = 284;
	Vertex[3].tag = true;

	Vertex[11].x = 252;	//����
	Vertex[11].y = 189;
	Vertex[11].tag = true;

	Vertex[9].x = 435;	//��һ
	Vertex[9].y = 296;
	Vertex[9].tag = true;

	Vertex[10].x = 375;	//��¥
	Vertex[10].y = 255;
	Vertex[10].tag = true;

	Vertex[4].x = 62;	//52#
	Vertex[4].y = 338;
	Vertex[4].tag = true;

	Vertex[7].x = 337;	//��̽¥
	Vertex[7].y = 427;
	Vertex[7].tag = false;

	Vertex[0].x = 3;	//��ˮ��
	Vertex[0].y = 176;
	Vertex[0].tag = true;

	Vertex[8].x = 312;	//����¥
	Vertex[8].y = 299;
	Vertex[8].tag = true;

	Vertex[1].x = 19;
	Vertex[1].y = 318;
	Vertex[1].tag = false;

	Vertex[5].x = 109;
	Vertex[5].y = 330;
	Vertex[5].tag = false;

	Vertex[6].x = 114;
	Vertex[6].y = 415;
	Vertex[6].tag = false;

	Vertex[13].x = 110;	
	Vertex[13].y = 284;
	Vertex[13].tag = false;

	Vertex[14].x = 368;
	Vertex[14].y = 187;
	Vertex[14].tag = false;

	Vertex[15].x = 373;
	Vertex[15].y = 297;
	Vertex[15].tag = false;

	Vertex[16].x = 250;
	Vertex[16].y = 420;
	Vertex[16].tag = false;

	for (int i = 0; i < 17; i++)
	{
		MyMap.insertVertex(Vertex[i]);
	}

	MyMap.insertEdge(0, 1, 186);
	MyMap.insertEdge(0, 2, 136);
	MyMap.insertEdge(1, 4, 53);
	MyMap.insertEdge(4, 5, 46);
	MyMap.insertEdge(2, 3, 35);
	MyMap.insertEdge(3, 13, 21);
	MyMap.insertEdge(13, 5, 46);
	MyMap.insertEdge(5, 6, 131);
	MyMap.insertEdge(6, 16, 128);
	MyMap.insertEdge(16, 7, 113);
	MyMap.insertEdge(15, 7, 148);
	MyMap.insertEdge(10, 15, 40);
	MyMap.insertEdge(8, 15, 50);
	MyMap.insertEdge(15, 9, 50);
	MyMap.insertEdge(8, 10, 80);
	MyMap.insertEdge(9, 10, 70);
	MyMap.insertEdge(10, 14, 79);
	MyMap.insertEdge(14, 11, 108);
	MyMap.insertEdge(11, 12, 132);
	MyMap.insertEdge(11, 16, 280);
	MyMap.insertEdge(12, 13, 104);
}

CMy2View::~CMy2View()
{
}

BOOL CMy2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CMy2View ����

void CMy2View::OnDraw(CDC *pDC)
{
	CMy2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	BITMAP bmpProperties;

	CString strFilename = _T("Map-3.bmp");

	HBITMAP bmpHandle = (HBITMAP)LoadImage(NULL,strFilename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	CBitmap bmpPicture;
	CDC mdcPicture;

	CRect rect;
	GetClientRect(&rect);

	CBitmap *bmpFromHandle = bmpPicture.FromHandle(bmpHandle);
	bmpPicture.Attach(bmpHandle);
	GetObject(bmpPicture, sizeof(bmpProperties), &bmpProperties);
	mdcPicture.CreateCompatibleDC(pDC);
	CBitmap * bmpPrevious = mdcPicture.SelectObject(bmpFromHandle);
//	pDC->BitBlt(0, 0, bmpProperties.bmWidth, bmpProperties.bmHeight, &mdcPicture, 0, 0, SRCCOPY);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &mdcPicture, 0, 0, bmpProperties.bmWidth, bmpProperties.bmHeight, SRCCOPY);

	SIZE sizeTotal;
	sizeTotal.cx = bmpProperties.bmWidth;
	sizeTotal.cy = bmpProperties.bmHeight;

	SetScrollSizes(MM_TEXT, sizeTotal);

	pDC->SelectObject(bmpPrevious);

	CPen pen(PS_SOLID, 6, RGB(0, 255, 0));
	pDC->SelectObject(&pen);
	pDC->Ellipse(3 - R, 176 + R, 3 + R, 176 - R);	//��ˮ��
	pDC->Ellipse(20 - R, 287 + R, 20 + R, 287 - R);	//ѧ��
	pDC->Ellipse(93 - R, 284 + R, 93 + R, 284 - R);	//������
	pDC->Ellipse(62 - R, 338 + R, 62 + R, 338 - R);	//52#
	pDC->Ellipse(110 - R, 189 + R, 110 + R, 189 - R);//���
	pDC->Ellipse(252 - R, 189 + R, 252 + R, 189 - R);	//����
	pDC->Ellipse(375 - R, 255 + R, 375 + R, 255 - R);	//��¥
	pDC->Ellipse(312 - R, 299 + R, 312 + R, 299 - R);	//����¥
	pDC->Ellipse(435 - R, 296 + R, 435 + R, 296 - R);	//��һ
	pDC->Ellipse(337 - R, 427 + R, 337 + R, 427 - R);	//��̽¥

	DeleteObject(bmpHandle);
}

void CMy2View::OnInitialUpdate()
{
	m_Info.Create(this, TTS_ALWAYSTIP);
	m_Info.AddTool(this, _T(""));
	m_Info.Activate(true);

	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMy2View ��ӡ

BOOL CMy2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy2View ���

#ifdef _DEBUG
void CMy2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy2Doc* CMy2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2Doc)));
	return (CMy2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2View ��Ϣ�������
bool inRange(int x, int y, int target_x, int target_y)
{
	if (x - target_x <= R&&x - target_x >= -R)
		if (y - target_y <= R&&y - target_y >= -R)
			return true;
	return false;
}

void CMy2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CScrollView::OnMouseMove(nFlags, point);

	CString str;
	str.Format(_T("X=%d Y=%d"), point.x, point.y);

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp() -> m_pMainWnd;
	pFrame->m_wndStatusBar.SetPaneText(2, str);

	int x = point.x;
	int y = point.y;

	if (inRange(x, y, 3, 176))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("��ˮ�� ����˼�����տ�ˮ�ĵط�"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 20, 287))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("��ʳ�� ���ǳԷ���λ��"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 93, 284))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("������ �е�Ӱ����λ��"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 62, 338))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("52�� ���ǵ�����¥"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 110, 189))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("��ѧ������� �����"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 252, 189))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("���� ƽ���Ͽε�λ��"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 375, 255))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("��¥ ��¥8¥�кõ�Ļ���"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 312, 299))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("����¥ ѧ��ѧ�ĵط�"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 435, 296))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("��һ¥ �Ͽε�λ�ã�����Ҳ��������"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 337, 427))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("��̽¥ ��δȥ���ĵط�"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}
	else
		m_Info.Activate(false);
}
