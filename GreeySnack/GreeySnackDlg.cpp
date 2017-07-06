
// GreeySnackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GreeySnack.h"
#include "GreeySnackDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGreeySnackDlg dialog




CGreeySnackDlg::CGreeySnackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGreeySnackDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGreeySnackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGreeySnackDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start, &CGreeySnackDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_Pause, &CGreeySnackDlg::OnBnClickedPause)
END_MESSAGE_MAP()


// CGreeySnackDlg message handlers

BOOL CGreeySnackDlg::OnInitDialog()
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
	DoDlgInit();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGreeySnackDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGreeySnackDlg::OnPaint()
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
HCURSOR CGreeySnackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGreeySnackDlg::DoDlgInit(){
	CFont font;
	font.CreatePointFont(200,_T("宋体"),NULL);
	GetDlgItem(IDC_Dispaly)->SetFont(&font);
	SetDlgItemTextW(IDC_Dispaly,_T("Welcome!Have a good fun!"));
	GetDlgItem(IDC_Pause)->EnableWindow(false);
}

void CGreeySnackDlg::ChangeWinSize(){
	static CRect oldRect(0,0,0,0);
	static CRect newRect(0,0,0,0);
	if(oldRect.IsRectNull()){
		GetWindowRect(&oldRect);
		newRect=oldRect;
		newRect.bottom-=20;
		SetWindowPos(NULL,newRect.left,newRect.top,newRect.Width(),newRect.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}else{
		SetWindowPos(NULL,oldRect.left,oldRect.top,oldRect.Width(),oldRect.Height(),SWP_NOMOVE|SWP_NOZORDER);
		oldRect=CRect(0,0,0,0);
	}
}

DWORD WINAPI StartOperator(LPVOID lpParameter){
	return TRUE;
}

void CGreeySnackDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemTextW(IDC_Dispaly,_T("Sorry!Noncompletely!"));
	GetDlgItem(IDC_Pause)->EnableWindow(true);
	GetDlgItem(IDC_Start)->EnableWindow(false);
	CreateThread(NULL,0,StartOperator,this,0,NULL);
	AfxMessageBox(_T("Sorry!Noncompletely!"));
}

DWORD WINAPI PauseOperator(LPVOID lpParameter){
	static_cast<CGreeySnackDlg*>(lpParameter)->ChangeWinSize();
	static_cast<CGreeySnackDlg*>(lpParameter)->GetDlgItem(IDC_Pause)->EnableWindow(false);
	static_cast<CGreeySnackDlg*>(lpParameter)->GetDlgItem(IDC_Start)->EnableWindow(true);
	AfxMessageBox(_T("线程调用成功！"));
	return TRUE;
}

void CGreeySnackDlg::OnBnClickedPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CreateThread(NULL,0,PauseOperator,this,0,NULL);
}

