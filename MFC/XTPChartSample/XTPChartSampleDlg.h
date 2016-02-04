
// XTPChartSampleDlg.h : header file
//

#pragma once


// CXTPChartSampleDlg dialog
class CXTPChartSampleDlg : public CDialogEx
{
// Construction
public:
	CXTPChartSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XTPCHARTSAMPLE_DIALOG };
#endif
	CXTPChartControl m_wndChartControl;

	void InitChart();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
