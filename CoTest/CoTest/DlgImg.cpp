// DlgImg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CoTest.h"
#include "DlgImg.h"
#include "afxdialogex.h"


// CDlgImg 대화 상자입니다.

//IMPLEMENT_DYNAMIC(CDlgImg, CDialogEx)
IMPLEMENT_SERIAL(CDlgImg, CDialogEx,1)
static int _nRadius;

CDlgImg::CDlgImg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgImg::IDD, pParent)
{
	m_pParent = pParent;
}

CDlgImg::~CDlgImg()
{
}

void CDlgImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgImg 메시지 처리기입니다.


BOOL CDlgImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0,0,640,480);

	initImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_Image)
	{
		m_Image.Draw(dc,0,0);
	}
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}

void CDlgImg::initImage()
{
	int n_Width = 640;
	int n_Height = 480;
	int n_Bpp = 8;

	m_Image.Create(n_Width, -n_Height,n_Bpp);

	if(n_Bpp == 8)
	{
		static RGBQUAD rgb[256];

		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

		m_Image.SetColorTable(0,256,rgb);
	}

	fm = (unsigned char*) m_Image.GetBits();

	memset(fm, 0xff, n_Width*n_Height);
}


void CDlgImg::UpdateInitCircle()
{
	static int nTemp=10;


	if(m_Image != NULL)
	{
		m_Image.Destroy();
		initImage();
	}
	srand((unsigned int)time(NULL));
	_nRadius = ((rand()%40)+5);
	CClientDC dc(this);

	moveCircle(_nRadius,INIT_CIRCLE);
	m_Image.Draw(dc,0,0);

}

void CDlgImg::UpdateCircle()
{
	static int nTemp=10;

	if(m_Image != NULL)
	{
		m_Image.Destroy();
		initImage();
	}


	CClientDC dc(this);
 	for (int i = 0; i < m_Image.GetWidth(); i++)
 	{
		
		if(moveCircle(_nRadius, UPDATE_CIRCLE))
			break;
		Sleep(10);

		m_Image.Draw(dc,0,0);
	
	}
}

BOOL CDlgImg::moveCircle(int n_Radius, int n_Step)
{
	static int n_StrX = 0;
	static int n_StrY = 0;
	static BOOL bFlag1 = FALSE;

	int nGray = 80;

	static int nStepX = 0;
	static int nStepY = 0;
	int n_Width = m_Image.GetWidth();
	int n_Height = m_Image.GetHeight();
	int n_Pitch = m_Image.GetPitch();

	fm = (unsigned char*) m_Image.GetBits();
	memset(fm, 0xff, n_Width*n_Height);

	if(!bFlag1 && (n_Step == 1))
	{

		if(nX1 < nX2)
		{
			n_StrX = nX1;
			nStepX = (nX2 - nX1)/40;
		}
		else
		{
			n_StrX = nX2;
			nStepX =  (nX1 - nX2)/40;
		}

		if(nY1 < nY2)
		{
			n_StrY = nY1;
			nStepY = (nY2 - nY1)/40;
		}
		else
		{
			n_StrY = nY2;
			nStepY = (nY1 - nY2)/40;
		}

		bFlag1 = TRUE;

	}


	DrawCircle(fm,n_StrX,n_StrY,n_Radius,nGray);

  	n_StrX += nStepX;
  	n_StrY += nStepY;

	if(((n_StrX>nX2) && (n_Step == 1)) || ((n_StrY > nY2) && (n_Step == 1)))
	{
		n_StrX = nX1;
		n_StrY = nY1;

		bFlag1 = FALSE;

		return TRUE;
	}


	GetCurrentDirectory(_MAX_PATH, m_DirPath.GetBuffer(_MAX_PATH+1));

	strFile.Format("\\Img%3d.bmp",n_StrX);

	str_Temp.Format("%s%s",m_DirPath,strFile);

	m_Image.Save(str_Temp);

	return FALSE;
}

void CDlgImg::DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{

	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_Image.GetPitch();


	for(int j = y; j < y+nRadius*2; j++)
	{
		for(int i = x; i < x+nRadius*2; i++)
		{
			if(isInCircle(i,j,nCenterX,nCenterY,nRadius))
				fm[j*nPitch + i] = nGray; 

		}
	}
}

BOOL CDlgImg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	BOOL bRet = FALSE;

	double dX = i-nCenterX;
	double dY = j-nCenterY;
	double dDist = dX * dX + dY * dY;

	if(dDist < (nRadius* nRadius))
		bRet = TRUE;

	return bRet;
}

void CDlgImg::initThread(int pX1, int pX2, int pY1, int pY2, int nOption)
{
	nX1 = pX1;
	nX2 = pX2;
	nY1 = pY1;
	nY2 = pY2;


	switch(nOption)
	{
	case 0:
		AfxBeginThread(&StartLocalThread1, this);
		break;

	case 1:
		AfxBeginThread(&StartLocalThread2, this);
		break;

	case 2:
		AfxBeginThread(&StartLocalThread3, this);
		break;

	default:
		break;
	}
}
UINT CDlgImg::StartLocalThread1(LPVOID pParam)
{

	((CDlgImg*)pParam)->UpdateInitCircle();
	
	return 0;
}

UINT CDlgImg::StartLocalThread2(LPVOID pParam)
{

	((CDlgImg*)pParam)->UpdateCircle();

	return 0;
}

UINT CDlgImg::StartLocalThread3(LPVOID pParam)
{
	((CDlgImg*)pParam)->ProcessImage();
	return 0;
}


void CDlgImg::ProcessImage()
{

	CString m_filename;
	CString m_filedir;

	CClientDC dc(this);
	CFileDialog fileDlg(TRUE,NULL,NULL,OFN_EXPLORER | OFN_HIDEREADONLY,"select file(*.bmp, *.jpg) | *.bmp; *.jpg");

	int iReturn = fileDlg.DoModal();

	if(iReturn == IDOK)
	{ 
		m_filename=fileDlg.GetFileName();     
		m_filedir=fileDlg.GetPathName();      
	}

	fileDlg.DestroyWindow();

 	if(m_Image != NULL)
 	{
		m_Image.Destroy();	
	}


	HRESULT hResult = m_Image.Load(m_filedir);
	if (FAILED(hResult))
	{
		CString msg;
		msg.Format("Error: Failed to image load %s", m_filedir);
		AfxMessageBox(msg);
		return;
	}
	
	m_Image.Draw(dc,0,0);

	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();

	CRect rect(0,0,640,480);

	unsigned char* _fm = (unsigned char*)m_Image.GetBits();;
	int nTh = 0x80;

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	int ntemp=0;

	
	for(int j = rect.top; j < rect.bottom; j++)
	{
		for(int i = rect.left; i < rect.right; i++)
		{
			if(_fm[j*nPitch+i] < nTh)
			{
				nSumY += j;
				nSumX += i;
				nCount++;
			}
	
		}
	}

	int nCenterX = nSumX / nCount;
	int nCenterY = nSumY / nCount;

	drawPen(nCenterX, nCenterY);
	
}

void CDlgImg::drawPen(int centerX, int centerY)
{
	CRect rect;
	CPen pen;

	pen.CreatePen(PS_SOLID, 1, RGB(0x50,0,0));
	
	CString csTemp;
	csTemp.Format(_T("%3d, %3d"), centerX, centerY);
	CDC* cDC;
	cDC = CDC::FromHandle(m_Image.GetDC());
	CPen* pOldPen = cDC->SelectObject(&pen);
	cDC->TextOut(centerX,centerY,csTemp);
	cDC->SelectObject(pOldPen);

	CClientDC dc(this);
	m_Image.Draw(dc,0,0);

	pen.DeleteObject();

	m_Image.ReleaseDC();
	ReleaseDC(cDC);


}


void CDlgImg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
}
