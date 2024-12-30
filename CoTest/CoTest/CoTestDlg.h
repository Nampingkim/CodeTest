
// CoTestDlg.h : 헤더 파일
//
#include "DlgImg.h"
#pragma once

#define DRAW_CIRCLE 0
#define MOVE_CIRCLE 1
#define CALC_CIRCLE 2
// CCoTestDlg 대화 상자
class CCoTestDlg : public CDialogEx
{
// 생성입니다.
private:
	int x1,y1,x2,y2;
	BOOL bFlag;
public:
	CCoTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	
	CDlgImg	*m_pDlgImg;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
