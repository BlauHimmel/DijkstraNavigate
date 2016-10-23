
// 2View.cpp : CMy2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

int transfer(int index)		//将combobox中的index转换为vertex中的下标
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
	STRdistance = _T("距离:") + STRdistance + _T("m");

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->m_wndStatusBar.SetPaneText(0, STRdistance);

	delete[] path;
	delete[] distance;
	delete[] result;
	return 0;
}

// CMy2View 构造/析构
CMy2View::CMy2View()
{
	// TODO:  在此处添加构造代码

	Info Vertex[17];

	Vertex[2].x = 19;	//学三
	Vertex[2].y = 287;
	Vertex[2].tag = true;

	Vertex[12].x = 110;	//大活
	Vertex[12].y = 189;
	Vertex[12].tag = true;

	Vertex[3].x = 93;	//弘毅堂
	Vertex[3].y = 284;
	Vertex[3].tag = true;

	Vertex[11].x = 252;	//教三
	Vertex[11].y = 189;
	Vertex[11].tag = true;

	Vertex[9].x = 435;	//教一
	Vertex[9].y = 296;
	Vertex[9].tag = true;

	Vertex[10].x = 375;	//主楼
	Vertex[10].y = 255;
	Vertex[10].tag = true;

	Vertex[4].x = 62;	//52#
	Vertex[4].y = 338;
	Vertex[4].tag = true;

	Vertex[7].x = 337;	//物探楼
	Vertex[7].y = 427;
	Vertex[7].tag = false;

	Vertex[0].x = 3;	//开水房
	Vertex[0].y = 176;
	Vertex[0].tag = true;

	Vertex[8].x = 312;	//数理楼
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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CMy2View 绘制

void CMy2View::OnDraw(CDC *pDC)
{
	CMy2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
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
	pDC->Ellipse(3 - R, 176 + R, 3 + R, 176 - R);	//开水房
	pDC->Ellipse(20 - R, 287 + R, 20 + R, 287 - R);	//学三
	pDC->Ellipse(93 - R, 284 + R, 93 + R, 284 - R);	//弘毅堂
	pDC->Ellipse(62 - R, 338 + R, 62 + R, 338 - R);	//52#
	pDC->Ellipse(110 - R, 189 + R, 110 + R, 189 - R);//大活
	pDC->Ellipse(252 - R, 189 + R, 252 + R, 189 - R);	//教三
	pDC->Ellipse(375 - R, 255 + R, 375 + R, 255 - R);	//主楼
	pDC->Ellipse(312 - R, 299 + R, 312 + R, 299 - R);	//数理楼
	pDC->Ellipse(435 - R, 296 + R, 435 + R, 296 - R);	//教一
	pDC->Ellipse(337 - R, 427 + R, 337 + R, 427 - R);	//物探楼

	DeleteObject(bmpHandle);
}

void CMy2View::OnInitialUpdate()
{
	m_Info.Create(this, TTS_ALWAYSTIP);
	m_Info.AddTool(this, _T(""));
	m_Info.Activate(true);

	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMy2View 打印

BOOL CMy2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy2View 诊断

#ifdef _DEBUG
void CMy2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy2Doc* CMy2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2Doc)));
	return (CMy2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2View 消息处理程序
bool inRange(int x, int y, int target_x, int target_y)
{
	if (x - target_x <= R&&x - target_x >= -R)
		if (y - target_y <= R&&y - target_y >= -R)
			return true;
	return false;
}

void CMy2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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
		m_Info.UpdateTipText(_T("开水房 顾名思义是烧开水的地方"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 20, 287))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("三食堂 我们吃饭的位置"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 93, 284))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("弘毅堂 有电影看的位置"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 62, 338))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("52栋 我们的寝室楼"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 110, 189))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("大学生活动中心 活动场所"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 252, 189))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("教三 平常上课的位置"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 375, 255))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("主楼 主楼8楼有好点的机房"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 312, 299))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("数理楼 学数学的地方"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 435, 296))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("教一楼 上课的位置，考试也多在这里"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}

	else if (inRange(x, y, 337, 427))
	{
		EnableToolTips(TRUE);
		m_Info.UpdateTipText(_T("物探楼 从未去过的地方"), this);
		m_Info.Update();
		m_Info.Activate(true);
		EnableToolTips(FALSE);
	}
	else
		m_Info.Activate(false);
}
