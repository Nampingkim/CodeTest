
// CoTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CoTest.h"
#include "CoTestDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CCoTestDlg ��ȭ ����




CCoTestDlg::CCoTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCoTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_WM_DESTROY()

	//ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DRAW, &CCoTestDlg::OnBnClickedDraw)
	ON_BN_CLICKED(IDC_ACTION, &CCoTestDlg::OnBnClickedAction)
	ON_BN_CLICKED(IDC_OPEN, &CCoTestDlg::OnBnClickedOpen)
END_MESSAGE_MAP()


// CCoTestDlg �޽��� ó����

BOOL CCoTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	x1 = 10;
	x2 = 500;
	y1 = 10;
	y2 = 400;

	CString csTemp;

	csTemp.Format("%3d",x1);
	SetDlgItemText(IDC_X1,csTemp);
	csTemp.Format("%3d",x2);
	SetDlgItemText(IDC_X2,csTemp);
	csTemp.Format("%3d",y1);
	SetDlgItemText(IDC_Y1,csTemp);
	csTemp.Format("%3d",y2);
	SetDlgItemText(IDC_Y2,csTemp);
	bFlag = FALSE;

	m_pDlgImg = new CDlgImg;
	m_pDlgImg->Create(IDD_DLGIMG, this);
	m_pDlgImg->ShowWindow(SW_SHOW);
	//SetTimer(IDD_COTEST_DIALOG,200,NULL);
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCoTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCoTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCoTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCoTestDlg::OnBnClickedDraw()
{

	bFlag = TRUE;
	getPoint();
	m_pDlgImg->initThread(x1, x2, y1, y2,DRAW_CIRCLE);
}

void CCoTestDlg::OnBnClickedAction()
{

	bFlag = TRUE;
	getPoint();
	m_pDlgImg->initThread(x1, x2, y1, y2,MOVE_CIRCLE);
}




void CCoTestDlg::OnBnClickedOpen()
{
	bFlag = TRUE;
	m_pDlgImg->ProcessImage();
}


void CCoTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(m_pDlgImg)
	{
		m_pDlgImg->DestroyWindow();
		delete m_pDlgImg;
	}
	WSACleanup();
	CoUninitialize();
	TRACE("byebye");
}





void CCoTestDlg::getPoint()
{
	if(bFlag)
	{
		CEdit *pEdit;
		CString pStr;
		int n_temp;
		
		pEdit = (CEdit *)GetDlgItem(IDC_X1);
		pEdit->GetWindowText(pStr);
		n_temp = atoi(pStr);

		if (n_temp>0)
			x1 = n_temp;

		pEdit = (CEdit *)GetDlgItem(IDC_X2);
		pEdit->GetWindowText(pStr);
		n_temp = atoi(pStr);
		
		if(n_temp>0)
			x2 = n_temp;

		pEdit = (CEdit *)GetDlgItem(IDC_Y1);
		pEdit->GetWindowText(pStr);
		n_temp = atoi(pStr);

		if(n_temp>0)
			y1 = n_temp;

		pEdit = (CEdit *)GetDlgItem(IDC_Y2);
		pEdit->GetWindowText(pStr);
		n_temp = atoi(pStr);


		if(n_temp>0)
			y2 = n_temp;



	}
}



