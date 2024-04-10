
// LabirintDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Labirint.h"
#include "LabirintDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CLabirintDlg



CLabirintDlg::CLabirintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABIRINT_DIALOG, pParent)
	, rows(0)
	, columns(0)
	, status(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLabirintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, My_picture);
	DDX_Text(pDX, IDC_EDIT1, rows);
	DDX_Text(pDX, IDC_EDIT2, columns);
	DDX_Text(pDX, IDC_EDIT3, status);
}

BEGIN_MESSAGE_MAP(CLabirintDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_VSCROLL()
//	ON_WM_TIMER()
//	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_FINDEXIT, &CLabirintDlg::OnBnClickedFindexit)
//	ON_WM_MOUSEWHEEL()
//	ON_WM_RBUTTONDOWN()
//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Обработчики сообщений CLabirintDlg

BOOL CLabirintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	ShowWindow(SW_MAXIMIZE);
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CLabirintDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CLabirintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CLabirintDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

//	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
	//MessageBox(L"Work in window!", L"Best", NULL);
	//if (my_timer != NULL) KillTimer(my_timer);
//	My_picture.translate_vertical = my_vertical.GetPos();
//	Invalidate(FALSE);
//}


//void CLabirintDlg::OnTimer(UINT_PTR nIDEvent)
//{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//	CDialogEx::OnTimer(nIDEvent);
//	if (My_picture.more_max_vertical > 0.)
//	{
//		my_vertical.SetRange(0, My_picture.more_max_vertical);
//		my_vertical.ShowWindow(TRUE);
//	}
//	else
//	{
//		my_vertical.SetPos(0);
//		my_vertical.ShowWindow(FALSE);
//	}
//	if (My_picture.more_max_gorizontal > 0.)
//	{
//		my_gorizontal.SetRange(0, My_picture.more_max_gorizontal);
//		my_gorizontal.ShowWindow(TRUE);
//	}
//	else
//	{
//		my_gorizontal.SetPos(0);
//		my_gorizontal.ShowWindow(FALSE);
//	}
//
//	if (My_picture.allow_draw == true)
//	{
//		Invalidate(FALSE);
//	}
//}


//void CLabirintDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

//	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
//	My_picture.translate_gorizontal = my_gorizontal.GetPos();
//	Invalidate(FALSE);
//}

DWORD __stdcall CLabirintDlg::My_thread(PVOID p)
{
	CLabirintDlg* my = (CLabirintDlg*)p;
	Create_labirint(my->My_picture.more_klet);
	Find_exit(my->My_picture.more_klet);
	my->status = L"draw";
	my->UpdateData(FALSE);
	my->Invalidate(FALSE);
	my->status = L"end";
	my->UpdateData(FALSE);
	return 0;
}

void CLabirintDlg::OnBnClickedFindexit()
{
	// TODO: добавьте свой код обработчика уведомлений
	//My_picture.allow_draw = true;
	//CreateThread(NULL, NULL, CLabirintDlg::thread_find, this, NULL, NULL);
	UpdateData(TRUE);
	My_picture.row = rows;
	My_picture.column = columns;
	My_picture.more_klet = Create_arr(rows, columns);
	My_picture.allow_draw = true;
	CreateThread(NULL, NULL, My_thread, this, NULL, NULL);
	status = L"work";
	UpdateData(FALSE);
	/*Create_labirint(My_picture.more_klet);
	Find_exit(My_picture.more_klet);
	Invalidate(FALSE);*/
	//status = L"end";
	//UpdateData(FALSE);
}


//BOOL CLabirintDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

//	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
//	MessageBox(L"Ura!", L" ", NULL);
//}

//void CLabirintDlg::OnRButtonDown(UINT nFlags, CPoint point)
//{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

//	CDialogEx::OnRButtonDown(nFlags, point);
//	My_picture.scale_lab -= 1;
//	Invalidate(FALSE);
//}


//void CLabirintDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

//	CDialogEx::OnLButtonDown(nFlags, point);
//	My_picture.scale_lab += 1;
//	Invalidate(FALSE);
//}
