#include "pch.h"
#include "Algor_lab.h"

My_kletka::My_kletka()
{
	up_wall = right_wall = down_wall = left_wall = true;
	color_path = color_tupic = color_visit = false;
}

My_kletka::~My_kletka()
{
}

vector<vector<My_kletka>> Create_arr(int row, int column)
{
	vector<vector<My_kletka>> my;
	vector < My_kletka > work;


	for (int j = 0; j < column; j++)
	{
		work.push_back(My_kletka());
	}

	for (int i = 0; i < row; i++)
	{
		my.push_back(work);
	}
	work.clear();

	return my;
}

void Create_labirint(vector<vector<My_kletka>>& many_kletok)
{
	srand(time(NULL));
	many_kletok[0][0].color_visit = true;
	vector <int> napravleniya = { 1, 2, 3, 4 }; // 1 - наверх, 2 - вправо, 3 - вниз, 4 - влево
	int my_row = 0, my_column = 0, all_kletki = many_kletok.size() * many_kletok[0].size(), cur_kletok = 1;
	vector <int> cur_napravleniya = napravleniya;
	vector<RowAndColumn> stek;
	RowAndColumn index;
	index.rows = 0;
	index.columns = 0;
	stek.push_back(index);

	while (cur_kletok < all_kletki)
	{
		if (cur_napravleniya.size() != 0)
		{
			random_shuffle(cur_napravleniya.begin(), cur_napravleniya.end(), myrandom);

			if (cur_napravleniya[0] == 1)
			{
				if (my_row - 1 < 0)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row - 1][my_column].color_visit == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				many_kletok[my_row][my_column].up_wall = false;
				my_row = my_row - 1;
				many_kletok[my_row][my_column].down_wall = false;
			}

			if (cur_napravleniya[0] == 2)
			{
				if (my_column + 1 > many_kletok[0].size() - 1)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row][my_column + 1].color_visit == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				many_kletok[my_row][my_column].right_wall = false;
				my_column = my_column + 1;
				many_kletok[my_row][my_column].left_wall = false;
			}

			if (cur_napravleniya[0] == 3)
			{
				if (my_row + 1 > many_kletok.size() - 1)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row + 1][my_column].color_visit == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				many_kletok[my_row][my_column].down_wall = false;
				my_row = my_row + 1;
				many_kletok[my_row][my_column].up_wall = false;
			}

			if (cur_napravleniya[0] == 4)
			{
				if (my_column - 1 < 0)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row][my_column - 1].color_visit == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				many_kletok[my_row][my_column].left_wall = false;
				my_column = my_column - 1;
				many_kletok[my_row][my_column].right_wall = false;
			}

			many_kletok[my_row][my_column].color_visit = true;

			if (my_row != many_kletok.size() - 1 || my_column != many_kletok[0].size() - 1)
			{
				index.rows = my_row;
				index.columns = my_column;
				stek.push_back(index);
			}
			else
			{
				my_row = stek[stek.size() - 1].rows;
				my_column = stek[stek.size() - 1].columns;
			}

			cur_napravleniya = napravleniya;
			cur_kletok++;
		}
		else
		{
			stek.pop_back();
			my_row = stek[stek.size() - 1].rows;
			my_column = stek[stek.size() - 1].columns;
			cur_napravleniya = napravleniya;
		}
	}
}

int myrandom(int i)
{
	return std::rand() % i;
}

void Find_exit(vector<vector<My_kletka>>& many_kletok)
{
	srand(time(NULL));
	many_kletok[0][0].color_path = true;
	vector <int> napravleniya = { 1, 2, 3, 4 }; // 1 - наверх, 2 - вправо, 3 - вниз, 4 - влево
	int my_row = 0, my_column = 0;
	vector <int> cur_napravleniya = napravleniya;
	vector<RowAndColumn> stek;
	RowAndColumn index;
	index.rows = 0;
	index.columns = 0;
	stek.push_back(index);

	while (my_row != many_kletok.size() - 1 || my_column != many_kletok[0].size() - 1)
	{
		if (cur_napravleniya.size() != 0)
		{
			random_shuffle(cur_napravleniya.begin(), cur_napravleniya.end(), myrandom);

			if (cur_napravleniya[0] == 1)
			{
				if (many_kletok[my_row][my_column].up_wall == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row - 1][my_column].color_path == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				my_row = my_row - 1;
			}

			if (cur_napravleniya[0] == 2)
			{
				if (many_kletok[my_row][my_column].right_wall == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row][my_column + 1].color_path == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				my_column = my_column + 1;
			}

			if (cur_napravleniya[0] == 3)
			{
				if (many_kletok[my_row][my_column].down_wall == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row + 1][my_column].color_path == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				my_row = my_row + 1;
			}

			if (cur_napravleniya[0] == 4)
			{
				if (many_kletok[my_row][my_column].left_wall == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				if (many_kletok[my_row][my_column - 1].color_path == true)
				{
					cur_napravleniya.erase(cur_napravleniya.begin());
					continue;
				}

				my_column = my_column - 1;
			}

			many_kletok[my_row][my_column].color_path = true;

			/*if (my_row != many_kletok.size() - 1 || my_column != many_kletok[0].size() - 1)
			{
				index.rows = my_row;
				index.columns = my_column;
				stek.push_back(index);
			}
			else
			{
				my_row = stek[stek.size() - 1].rows;
				my_column = stek[stek.size() - 1].columns;
			}*/

			index.rows = my_row;
			index.columns = my_column;
			stek.push_back(index);

			cur_napravleniya = napravleniya;
			//cur_kletok++;
		}
		else
		{
			many_kletok[my_row][my_column].color_tupic = true;
			stek.pop_back();
			my_row = stek[stek.size() - 1].rows;
			my_column = stek[stek.size() - 1].columns;
			cur_napravleniya = napravleniya;
		}
	}
}
