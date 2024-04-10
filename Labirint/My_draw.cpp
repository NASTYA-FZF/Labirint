// My_draw.cpp: файл реализации
//
#include "pch.h"
#include "Labirint.h"
#include "My_draw.h"
using namespace Gdiplus;

// My_draw

IMPLEMENT_DYNAMIC(My_draw, CStatic)

My_draw::My_draw()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&token, &input, NULL);
	if (s != Ok) MessageBox(L"s != Ok", L"Error", NULL);
	row = 0;
	column = 0;
	more_max_vertical = 0.;
	translate_vertical = 0.;
	more_max_gorizontal = 0.;
	translate_gorizontal = 0.;
	allow_draw = false;
	scale_lab = 1;
	file = false;
}

My_draw::~My_draw()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(My_draw, CStatic)
	ON_WM_VSCROLL()
//	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// Обработчики сообщений My_draw




void My_draw::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  Добавьте исходный код для отображения указанного элемента
	Graphics g(lpDrawItemStruct->hDC);
	Bitmap buffer(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &g);
	Graphics gr(&buffer);

	Matrix matr;
	matr.Translate(-translate_gorizontal, -translate_vertical);
	matr.Scale(scale_lab, scale_lab);
	gr.SetTransform(&matr);

	gr.Clear({ 255, 204, 204, 255 });

	Rect main_wnd(lpDrawItemStruct->rcItem.left + translate_gorizontal - 10, lpDrawItemStruct->rcItem.top + translate_vertical - 10, lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left + 10, lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top + 10);

	if (row != 0 && column != 0)
	{
		Pen my_pen({ 255, 255, 43, 43 }, 2);
		Pen pen_path({ 255, 66, 170, 255 }, 2);
		Pen pen_tupic({ 255, 0, 69, 36 }, 2);
		Pen pen_visit({ 255, 167, 252, 0 }, 2);

		SolidBrush* mySolidBrush_visit = new SolidBrush({ 255, 167, 252, 0 });
		SolidBrush* mySolidBrush_path = new SolidBrush({ 255, 66, 170, 255 });
		SolidBrush* mySolidBrush_tupic = new SolidBrush({ 255, 0, 69, 36 });

		double step_gorizontal = (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) / (double)column;
		double step_vertical = (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) / (double)row;

		//if (step_vertical < 10)
		//{
		//	step_vertical = 10;
		//	more_max_vertical = step_vertical * row - (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) + 10;
		//}
		//else more_max_vertical = 0.;

		//if (step_gorizontal < 10)
		//{
		//	step_gorizontal = 10;
		//	more_max_gorizontal = step_gorizontal * column - (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) + 10;
		//}
		//else more_max_gorizontal = 0.;

		for (int i = 1; i < row + 1; i++)
		{
			for (int j = 1; j < column + 1; j++)
			{
				//if (!main_wnd.Contains(Point((j - 1) * step_gorizontal, (i - 1) * step_vertical))) continue;
				Rect rectan((j - 1) * step_gorizontal, (i - 1) * step_vertical, step_gorizontal, step_vertical);

				if (more_klet[i - 1][j - 1].color_tupic == true)
				{
					//gr.DrawRectangle(&pen_tupic, rectan);
					gr.FillRectangle(mySolidBrush_tupic, rectan);
					if (more_klet[i - 1][j - 1].up_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical)); //верхняя
					else gr.DrawLine(&pen_tupic, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical));

					if (more_klet[i - 1][j - 1].right_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical)); //правая
					else gr.DrawLine(&pen_tupic, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical));

					if (more_klet[i - 1][j - 1].down_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical)); //нижняя
					else gr.DrawLine(&pen_tupic, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical));

					if (more_klet[i - 1][j - 1].left_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical)); //левая
					else gr.DrawLine(&pen_tupic, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical));
					continue;
				}

				if (more_klet[i - 1][j - 1].color_path == true)
				{
					//gr.DrawRectangle(&pen_path, rectan);
					gr.FillRectangle(mySolidBrush_path, rectan);
					if (more_klet[i - 1][j - 1].up_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical)); //верхняя
					else gr.DrawLine(&pen_path, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical));

					if (more_klet[i - 1][j - 1].right_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical)); //правая
					else gr.DrawLine(&pen_path, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical));

					if (more_klet[i - 1][j - 1].down_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical)); //нижняя
					else gr.DrawLine(&pen_path, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical));

					if (more_klet[i - 1][j - 1].left_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical)); //левая
					else gr.DrawLine(&pen_path, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical));
					continue;
				}

				if (more_klet[i - 1][j - 1].color_visit == true)
				{
					//gr.DrawRectangle(&pen_visit, rectan);
					gr.FillRectangle(mySolidBrush_visit, rectan);
					if (more_klet[i - 1][j - 1].up_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical)); //верхняя
					else gr.DrawLine(&pen_visit, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical));

					if (more_klet[i - 1][j - 1].right_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical)); //правая
					else gr.DrawLine(&pen_visit, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical), Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical));

					if (more_klet[i - 1][j - 1].down_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical)); //нижняя
					else gr.DrawLine(&pen_visit, Point((j - 1) * step_gorizontal + step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical));

					if (more_klet[i - 1][j - 1].left_wall == true) gr.DrawLine(&my_pen, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical)); //левая
					else gr.DrawLine(&pen_visit, Point((j - 1) * step_gorizontal, (i - 1) * step_vertical + step_vertical), Point((j - 1) * step_gorizontal, (i - 1) * step_vertical));
				}
			}
		}
	}

	//buffer.Save(L"C://Users//79159//Desktop//ННГУ новый//Моделирование систем//Labirint//Labirint//screen.png", &png);

	g.DrawImage(&buffer, 0, 0, 0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, UnitPixel);
}

//BOOL My_draw::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

//	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
//	scale_lab = zDelta;
//}
