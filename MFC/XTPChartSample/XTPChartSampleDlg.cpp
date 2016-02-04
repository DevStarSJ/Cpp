
// XTPChartSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XTPChartSample.h"
#include "XTPChartSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CXTPChartSampleDlg dialog

CXTPChartSampleDlg::CXTPChartSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_XTPCHARTSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXTPChartSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
}

BEGIN_MESSAGE_MAP(CXTPChartSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CXTPChartSampleDlg message handlers

BOOL CXTPChartSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitChart();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXTPChartSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXTPChartSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXTPChartSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CXTPChartSampleDlg::InitChart()
{
	// Content를 이용해서 Chart의 Title, Series, Legends등의 설정이 가능
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	if (!pContent) return;

	pContent->GetLegend()->SetVisible(TRUE);

	// Title 설정
	CXTPChartTitleCollection* pTitles = pContent->GetTitles();
	if (pTitles)
	{
		CXTPChartTitle* pTitle = pTitles->Add(new CXTPChartTitle());
		if (pTitle)
		{
			pTitle->SetText(_T("My Chart"));
		}
	}

	// Series, Series Point 추가
	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	if (pCollection)
	{
		CXTPChartSeries* pSeries = pCollection->Add(new CXTPChartSeries());
		if (pSeries)
		{
			pSeries->SetName(_T("Series1"));
			pSeries->SetStyle(new CXTPChartLineSeriesStyle());
			CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
			if (pPoints)
			{
				pPoints->Add(new CXTPChartSeriesPoint(0, 3));
				pPoints->Add(new CXTPChartSeriesPoint(1, 1));
				pPoints->Add(new CXTPChartSeriesPoint(2, 2));
				pPoints->Add(new CXTPChartSeriesPoint(3, 0.5));

				double dArithmeticMean = pPoints->GetArithmeticMean(0);
				double dStd = pPoints->GetStandardDeviation(0);

			}
		}

		CXTPChartSeries* pS2 = pCollection->Add(new CXTPChartSeries());
		if (pS2)
		{
			pS2->SetName(_T("Series2"));
			pS2->SetStyle(new CXTPChartLineSeriesStyle());
			CXTPChartSeriesPointCollection* pPoints = pS2->GetPoints();
			if (pPoints)
			{
				pPoints->Add(new CXTPChartSeriesPoint(0, 2));
				pPoints->Add(new CXTPChartSeriesPoint(1, 0.5));
				pPoints->Add(new CXTPChartSeriesPoint(2, 3));
				pPoints->Add(new CXTPChartSeriesPoint(3, 1));
			}
		}

		// SeriesLabel의 설정
		for (int i = 0; i < pCollection->GetCount(); i++)
		{
			CXTPChartSeriesLabel* pLabel = pCollection->GetAt(i)->GetStyle()->GetLabel();
			pLabel->GetFormat()->SetCategory(xtpChartNumber);
			pLabel->GetFormat()->SetDecimalPlaces(1); // 소숫점 표시
			pLabel->SetVisible(FALSE);
		}

		// Axis 설정
		//CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
		CXTPChartDiagram* pDiagram = pCollection->GetAt(0)->GetDiagram();
		CXTPChartDiagram2D* pD2D = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pDiagram);
		if (pD2D)
		{
			CXTPChartAxis *pAxisX = pD2D->GetAxisX();
			if (pAxisX)
			{
				CXTPChartAxisTitle* pTitle = pAxisX->GetTitle();
				if (pTitle)
				{
					pTitle->SetText(_T("X-Argument"));
					pTitle->SetVisible(TRUE);
				}
			}

			CXTPChartAxis *pAxisY = pD2D->GetAxisY();
			if (pAxisX)
			{
				CXTPChartAxisTitle* pTitle = pAxisY->GetTitle();
				if (pTitle)
				{
					pTitle->SetText(_T("Y-Value"));
					pTitle->SetVisible(TRUE);
				}
			}
		}

		// Marker 안보이게 하기
		for (int i = 0; i < pCollection->GetCount(); i++)
		{
			CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pCollection->GetAt(i)->GetStyle();
			pStyle->GetMarker()->SetVisible(FALSE);
			//pStyle->GetMarker()->SetSize(20); // Maeker Size 조정
			//pStyle->GetMarker()->SetType(xtpChartMarkerCircle); // enum XTPChartMarkerType 
		}

		pD2D->SetAllowZoom(TRUE);	// 마우스 휠을 이용한 Zoom 허용
		pD2D->SetAllowScroll(TRUE); // Scroll 허용


		m_wndChartControl.SaveAsImage(_T("D:\\A.PNG"),CSize(600,400));

	}
}