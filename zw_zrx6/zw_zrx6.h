// zw_zrx6.h : main header file for the zw_zrx6 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Czw_zrx6App
// See zw_zrx6.cpp for the implementation of this class
//

class Czw_zrx6App : public CWinApp
{
public:
	Czw_zrx6App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
