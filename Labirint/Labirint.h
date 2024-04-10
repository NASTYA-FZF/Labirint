
// Labirint.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLabirintApp:
// Сведения о реализации этого класса: Labirint.cpp
//

class CLabirintApp : public CWinApp
{
public:
	CLabirintApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CLabirintApp theApp;
