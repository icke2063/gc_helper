//============================================================================
// Name        : SudokuSolver.cpp
// Author      : icke2063
// Version     :
// Copyright   : Your copyright notice
// Description : Sudoku Solver (BruteForce ;) )
//============================================================================

#include <iostream>
using namespace std;
#include <stdint.h>
#include <list>
#include <string.h>
#include <stdlib.h>


struct condition
{
	uint8_t x;
	uint8_t y;
};

struct conditions
{
	condition cur[9];
};

std::list<struct conditions> condi;


void printSudoku(uint8_t sudoku[9][9])
{
	cout << "printSudoku:" << std::hex << (long)&sudoku[0][0] << endl; // prints !!!Hello World!!!

	for(int x = 0;x<9;x++)
	{
		for(int y = 0;y<9;y++)
		{
			cout << "[" <<  (int)sudoku[x][y]<< "]";
		}
		cout << endl;

	}
}

bool checkSudoku(uint8_t sudoku[9][9], bool hard = false)
{
	uint8_t tmp_array[9];

	for(std::list<struct conditions>::iterator it_condi = condi.begin();it_condi != condi.end(); ++it_condi)
	{

		memset(tmp_array, 0, 9);

		if(hard)
		{
			for(int i = 0;i<9;i++)
			{
				if(  sudoku[(*it_condi).cur[i].x][(*it_condi).cur[i].y] == 0)
				{// valid value at this position -> check it
					return false;
				}
			}
		}



		for(int i = 0;i<9;i++)
		{
			if(  sudoku[(*it_condi).cur[i].x][(*it_condi).cur[i].y] != 0)
			{// valid value at this position -> check it

				if(tmp_array[ sudoku[(*it_condi).cur[i].x][(*it_condi).cur[i].y] - 1] == 0 )
				{
					//mark unset value
					tmp_array[ sudoku[(*it_condi).cur[i].x][(*it_condi).cur[i].y] - 1] = 1;
				}
				else
				{
//					cout << "used[" <<  (int)(*it_condi).cur[i].x << "][" << (int)(*it_condi).cur[i].y
//											<< "]:" << (int)sudoku[(*it_condi).cur[i].x][(*it_condi).cur[i].y] << endl;

					return false;
				}
			}
		}
	}
	return true;
}

bool solveSudoku(uint8_t sudoku[9][9])
{

	uint8_t local_sudoku[9][9];
	for(int x = 0;x<9;x++)
	{
		for(int y = 0;y<9;y++)
		{
			local_sudoku[x][y] = sudoku[x][y];
		}
	}


	for(int x=0;x<9;x++)
	{
		for(int y = 0;y<9;y++)
		{
			if(local_sudoku[x][y] == 0)
			{

				//check sudoku
				if(checkSudoku(local_sudoku))
				{
					//try all combination for this part
					for(int cur_idea = 1;cur_idea <=9;cur_idea++)
					{
						local_sudoku[x][y] = cur_idea;

						printSudoku(local_sudoku);

						if(solveSudoku(local_sudoku))
						{
							return true;
						}
					}
				}
			}
			else
			{
				//check sudoku
				if(checkSudoku(local_sudoku, true))
				{
					return true;
				}
			}
		}
		cout << endl;
	}

	return false;
}


#define fillrow(X,a,b,c,d,e,f,g,h,i)	feld[X][0] = a;feld[X][1] = b;feld[X][2] = c;feld[X][3] = d;feld[X][4] = e;feld[X][5] = f; feld[X][6] = g;feld[X][7] = h;feld[X][8] = i;


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	uint8_t feld[9][9];

	memset(feld, 0, 9 * 9);

	struct conditions tmp_condi;

	//reihen
	for(int x = 0; x<9;x++)
	{
		for(int y = 0; y<9;y++)
		{
			tmp_condi.cur[y].x = x;	tmp_condi.cur[y].y = y;
		}
		condi.push_back(tmp_condi);
	}

	//spalten
	for(int y = 0; y<9;y++)
	{
		for(int x = 0;x<9;x++)
		{
			tmp_condi.cur[x].x = x;	tmp_condi.cur[x].y = y;
		}
		condi.push_back(tmp_condi);
	}

	//special
//	tmp_condi.cur[0].x = 0;	tmp_condi.cur[0].y = 0;
//	tmp_condi.cur[1].x = 0;	tmp_condi.cur[1].y = 1;
//	tmp_condi.cur[2].x = 0;	tmp_condi.cur[2].y = 2;
//	tmp_condi.cur[3].x = 0;	tmp_condi.cur[3].y = 3;
//	tmp_condi.cur[4].x = 0;	tmp_condi.cur[4].y = 4;
//	tmp_condi.cur[5].x = 0;	tmp_condi.cur[5].y = 5;
//	tmp_condi.cur[6].x = 1;	tmp_condi.cur[6].y = 3;
//	tmp_condi.cur[7].x = 1;	tmp_condi.cur[7].y = 4;
//	tmp_condi.cur[8].x = 1;	tmp_condi.cur[8].y = 5;
//	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 0;	tmp_condi.cur[0].y = 0;
	tmp_condi.cur[1].x = 0;	tmp_condi.cur[1].y = 1;
	tmp_condi.cur[2].x = 0;	tmp_condi.cur[2].y = 2;
	tmp_condi.cur[3].x = 0;	tmp_condi.cur[3].y = 3;
	tmp_condi.cur[4].x = 1;	tmp_condi.cur[4].y = 1;
	tmp_condi.cur[5].x = 2;	tmp_condi.cur[5].y = 1;
	tmp_condi.cur[6].x = 3;	tmp_condi.cur[6].y = 1;
	tmp_condi.cur[7].x = 4;	tmp_condi.cur[7].y = 1;
	tmp_condi.cur[8].x = 4;	tmp_condi.cur[8].y = 2;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 1;	tmp_condi.cur[0].y = 0;
	tmp_condi.cur[1].x = 2;	tmp_condi.cur[1].y = 0;
	tmp_condi.cur[2].x = 3;	tmp_condi.cur[2].y = 0;
	tmp_condi.cur[3].x = 4;	tmp_condi.cur[3].y = 0;
	tmp_condi.cur[4].x = 5;	tmp_condi.cur[4].y = 0;
	tmp_condi.cur[5].x = 6;	tmp_condi.cur[5].y = 0;
	tmp_condi.cur[6].x = 7;	tmp_condi.cur[6].y = 0;
	tmp_condi.cur[7].x = 5;	tmp_condi.cur[7].y = 1;
	tmp_condi.cur[8].x = 6;	tmp_condi.cur[8].y = 1;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 0;	tmp_condi.cur[0].y = 4;
	tmp_condi.cur[1].x = 0;	tmp_condi.cur[1].y = 5;
	tmp_condi.cur[2].x = 1;	tmp_condi.cur[2].y = 2;
	tmp_condi.cur[3].x = 1;	tmp_condi.cur[3].y = 3;
	tmp_condi.cur[4].x = 1;	tmp_condi.cur[4].y = 4;
	tmp_condi.cur[5].x = 2;	tmp_condi.cur[5].y = 2;
	tmp_condi.cur[6].x = 2;	tmp_condi.cur[6].y = 4;
	tmp_condi.cur[7].x = 2;	tmp_condi.cur[7].y = 5;
	tmp_condi.cur[8].x = 3;	tmp_condi.cur[8].y = 4;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 0;	tmp_condi.cur[0].y = 6;
	tmp_condi.cur[1].x = 0;	tmp_condi.cur[1].y = 7;
	tmp_condi.cur[2].x = 0;	tmp_condi.cur[2].y = 8;
	tmp_condi.cur[3].x = 1;	tmp_condi.cur[3].y = 5;
	tmp_condi.cur[4].x = 1;	tmp_condi.cur[4].y = 6;
	tmp_condi.cur[5].x = 1;	tmp_condi.cur[5].y = 8;
	tmp_condi.cur[6].x = 2;	tmp_condi.cur[6].y = 6;
	tmp_condi.cur[7].x = 3;	tmp_condi.cur[7].y = 6;
	tmp_condi.cur[8].x = 3;	tmp_condi.cur[8].y = 7;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 1;	tmp_condi.cur[0].y = 7;
	tmp_condi.cur[1].x = 2;	tmp_condi.cur[1].y = 7;
	tmp_condi.cur[2].x = 2;	tmp_condi.cur[2].y = 8;
	tmp_condi.cur[3].x = 3;	tmp_condi.cur[3].y = 8;
	tmp_condi.cur[4].x = 4;	tmp_condi.cur[4].y = 7;
	tmp_condi.cur[5].x = 4;	tmp_condi.cur[5].y = 8;
	tmp_condi.cur[6].x = 5;	tmp_condi.cur[6].y = 7;
	tmp_condi.cur[7].x = 5;	tmp_condi.cur[7].y = 8;
	tmp_condi.cur[8].x = 6;	tmp_condi.cur[8].y = 8;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 2;	tmp_condi.cur[0].y = 3;
	tmp_condi.cur[1].x = 3;	tmp_condi.cur[1].y = 2;
	tmp_condi.cur[2].x = 3;	tmp_condi.cur[2].y = 3;
	tmp_condi.cur[3].x = 3;	tmp_condi.cur[3].y = 5;
	tmp_condi.cur[4].x = 4;	tmp_condi.cur[4].y = 3;
	tmp_condi.cur[5].x = 4;	tmp_condi.cur[5].y = 4;
	tmp_condi.cur[6].x = 4;	tmp_condi.cur[6].y = 5;
	tmp_condi.cur[7].x = 4;	tmp_condi.cur[7].y = 6;
	tmp_condi.cur[8].x = 5;	tmp_condi.cur[8].y = 4;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 5;	tmp_condi.cur[0].y = 2;
	tmp_condi.cur[1].x = 5;	tmp_condi.cur[1].y = 3;
	tmp_condi.cur[2].x = 6;	tmp_condi.cur[2].y = 2;
	tmp_condi.cur[3].x = 6;	tmp_condi.cur[3].y = 3;
	tmp_condi.cur[4].x = 7;	tmp_condi.cur[4].y = 1;
	tmp_condi.cur[5].x = 7;	tmp_condi.cur[5].y = 2;
	tmp_condi.cur[6].x = 8;	tmp_condi.cur[6].y = 0;
	tmp_condi.cur[7].x = 8;	tmp_condi.cur[7].y = 1;
	tmp_condi.cur[8].x = 8;	tmp_condi.cur[8].y = 2;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 5;	tmp_condi.cur[0].y = 5;
	tmp_condi.cur[1].x = 5;	tmp_condi.cur[1].y = 6;
	tmp_condi.cur[2].x = 6;	tmp_condi.cur[2].y = 4;
	tmp_condi.cur[3].x = 6;	tmp_condi.cur[3].y = 5;
	tmp_condi.cur[4].x = 7;	tmp_condi.cur[4].y = 3;
	tmp_condi.cur[5].x = 7;	tmp_condi.cur[5].y = 4;
	tmp_condi.cur[6].x = 7;	tmp_condi.cur[6].y = 5;
	tmp_condi.cur[7].x = 7;	tmp_condi.cur[7].y = 6;
	tmp_condi.cur[8].x = 8;	tmp_condi.cur[8].y = 3;
	condi.push_back(tmp_condi);

	tmp_condi.cur[0].x = 6;	tmp_condi.cur[0].y = 6;
	tmp_condi.cur[1].x = 6;	tmp_condi.cur[1].y = 7;
	tmp_condi.cur[2].x = 7;	tmp_condi.cur[2].y = 7;
	tmp_condi.cur[3].x = 7;	tmp_condi.cur[3].y = 8;
	tmp_condi.cur[4].x = 8;	tmp_condi.cur[4].y = 4;
	tmp_condi.cur[5].x = 8;	tmp_condi.cur[5].y = 5;
	tmp_condi.cur[6].x = 8;	tmp_condi.cur[6].y = 6;
	tmp_condi.cur[7].x = 8;	tmp_condi.cur[7].y = 7;
	tmp_condi.cur[8].x = 8;	tmp_condi.cur[8].y = 8;
	condi.push_back(tmp_condi);



	fillrow(0,0,2,0,0,0,0,7,0,0);
	fillrow(1,0,0,0,0,0,0,0,9,0);
	fillrow(2,8,0,0,0,0,0,9,0,0);

	fillrow(3,7,0,0,4,0,0,0,2,0);
	fillrow(4,0,7,0,5,0,3,0,0,0);
	fillrow(5,0,0,0,0,0,0,0,0,8);

	fillrow(6,0,1,9,0,0,0,0,3,0);
	fillrow(7,0,0,0,6,0,0,0,0,0);

	if( solveSudoku(feld))
	{
		cout << "!!!success!!!" << endl; // prints !!!Hello World!!!
	}
	else
	{
		cout << "!!!failure!!!" << endl; // prints !!!Hello World!!!
	}



	return 0;
}


