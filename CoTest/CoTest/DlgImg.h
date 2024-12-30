#include <sys/timeb.h>  
#pragma once


// CDlgImg ��ȭ �����Դϴ�.

#define INIT_CIRCLE 0
#define UPDATE_CIRCLE 1

class CDlgImg : public CDialogEx
{
	//DECLARE_DYNAMIC(CDlgImg)
	DECLARE_SERIAL(CDlgImg)


		int nX1, nX2, nY1, nY2;

public:
	CDlgImg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgImg();

	CWnd *m_pParent;
	CImage m_Image;

	unsigned char* fm;

	CTime c_Time;
	CString strFile,str_Temp,m_DirPath;


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLGIMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	static UINT StartLocalThread1(LPVOID pParam);
	static UINT StartLocalThread2(LPVOID pParam);
	static UINT StartLocalThread3(LPVOID pParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void initImage();
	void ProcessImage();
	BOOL moveCircle(int n_Radius, int n_Step);
	void UpdateCircle();
	void UpdateInitCircle();
	BOOL isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);

	void drawPen(int centerX, int centerY);
	void initThread(int pX1, int pX2, int pY1, int pY2,int nOption);
	afx_msg void OnDestroy();
};
