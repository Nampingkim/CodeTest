
// CoTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

#include <atlimage.h>
// CCoTestApp:
// �� Ŭ������ ������ ���ؼ��� CoTest.cpp�� �����Ͻʽÿ�.
//

class CCoTestApp : public CWinApp
{
public:
	CCoTestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCoTestApp theApp;