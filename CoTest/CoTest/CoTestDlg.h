
// CoTestDlg.h : ��� ����
//
#include "DlgImg.h"
#pragma once

#define DRAW_CIRCLE 0
#define MOVE_CIRCLE 1
#define CALC_CIRCLE 2
// CCoTestDlg ��ȭ ����
class CCoTestDlg : public CDialogEx
{
// �����Դϴ�.
private:
	int x1,y1,x2,y2;
	BOOL bFlag;
public:
	CCoTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	
	CDlgImg	*m_pDlgImg;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();

	void getPoint();

	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedDraw();
	afx_msg void OnBnClickedAction();
	afx_msg void OnBnClickedOpen();
};
