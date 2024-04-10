#pragma once
#include <gdiplus.h>
#include "Algor_lab.h"

// My_draw

class My_draw : public CStatic
{
	DECLARE_DYNAMIC(My_draw)

public:
	My_draw();
	virtual ~My_draw();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	ULONG_PTR token;
	int column;
	int row;
	double more_max_vertical;
	double translate_vertical;
	double more_max_gorizontal;
	double translate_gorizontal;
	vector <vector < My_kletka > > more_klet;
	bool allow_draw;
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	short scale_lab;
	bool file;
};


