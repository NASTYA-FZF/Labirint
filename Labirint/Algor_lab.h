#pragma once
#include <vector>
#include <algorithm>
using namespace std;

struct RowAndColumn
{
	int rows;
	int columns;
};

class My_kletka
{
public:
	bool up_wall;
	bool right_wall;
	bool down_wall;
	bool left_wall;
	bool color_visit;
	bool color_path;
	bool color_tupic;

	My_kletka();

	~My_kletka();
};

vector < vector < My_kletka > > Create_arr(int row, int column);

void Create_labirint(vector < vector < My_kletka > >& many_kletok);

int myrandom(int i);

void Find_exit(vector < vector < My_kletka > >& many_kletok);