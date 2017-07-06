
// GreeySnack.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGreeySnackApp:
// See GreeySnack.cpp for the implementation of this class
//

class CGreeySnackApp : public CWinApp
{
public:
	CGreeySnackApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGreeySnackApp theApp;