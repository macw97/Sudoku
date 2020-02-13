#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#define _WIN32_WINNT 0x0500  //*
#include <windows.h>      //"windows.h"
#include <fcntl.h>  //for _setmode
#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#define UNASSIGNED 0
#define GRX 13
#define GRY 26
#define GRIDX 9
#define GRIDY 9
using namespace std;
typedef vector <vector <int> > SudokuGrid;

void PlaceCursor(const int x, const int y);

class Sudoku
{
private:
	char temp[GRX][GRY] = { "=========================",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "=========================",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "=========================",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "| 0 0 0 | 0 0 0 | 0 0 0 |",
					   "=========================" };
	int x = 2;
	int y = 1;
	queue<char> helper; //By queue i am able to work with cursor which modify elements in 2d char array
	SudokuGrid grid;
	vector<int> guessNum;
	SudokuGrid copy_grid;
	vector<int> gridPos;
	int difficulty;
	char temp_copy[GRX][GRY];
public:

		Sudoku();
		void set_difficulty(int number);
		void converToChar();
		void convertToInt();
		void temporary_copy();
		bool FindUnassignedLocation(int& row, int& col);
		bool isSafe(int row, int col, int num);
		bool UsedInCol(int col, int num);
		bool UsedInBox(int boxStartRow, int boxStartCol, int num);
		bool UsedInRow(int row, int num);
		bool SolveSudoku();
		bool check();
		void CopyToOriginal();
		void Copygrid();
		void clearBox();
		void countSoln(int& number);
		void removeNum();
		void print();
		void move(int V, int H);
		void reverseQueue(queue<char> & Queue);
		void put(char number);
	};

