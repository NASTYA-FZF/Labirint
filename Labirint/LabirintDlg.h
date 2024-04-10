
// LabirintDlg.h: файл заголовка
//

#pragma once
#include "My_draw.h"

// Диалоговое окно CLabirintDlg
class CLabirintDlg : public CDialogEx
{
// Создание
public:
	CLabirintDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABIRINT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	My_draw My_picture;
	int rows;
	int columns;
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	UINT_PTR my_timer;
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	static DWORD WINAPI My_thread(PVOID);
	afx_msg void OnBnClickedFindexit();
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CString status;
};
