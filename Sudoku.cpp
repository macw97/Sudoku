#include "Sudoku.h"

void PlaceCursor(const int x, const int y) {
	//My random generator for random shuffle

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD PlaceCursorHere;
	PlaceCursorHere.X = x;
	PlaceCursorHere.Y = y;

	SetConsoleCursorPosition(hConsole, PlaceCursorHere);
	return;
}

Sudoku::Sudoku()
{
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> randomer(1, 9);
	//Initialize grid
	grid.resize(GRIDX, vector<int>(GRIDY));
	for (int i = 0; i < GRIDX; i++)
	{
		for (int j = 0; j < GRIDY; j++)
		{
			grid[i][j] = 0;
		}
	}
	for (int i = 0; i < 81; i++)
	{
		gridPos.push_back(i);
	}
	random_shuffle(gridPos.begin(), gridPos.end());
	//random_shuffle(gridPos.begin(), gridPos.end(), myrandom);
	for (int i = 0; i < 6; i++)
	{
		int row = gridPos[i] / 9;
		int col = (gridPos[i]) % 9;
		int num = randomer(rng);
		if (isSafe(row, col, num))
		{
			grid[row][col] = num;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		guessNum.push_back(i + 1);
	}

	random_shuffle(guessNum.begin(), guessNum.end());

}
void Sudoku::temporary_copy()
{
	for (int i = 0; i < GRX; i++)
	{
		for (int j = 0; j < GRY; j++)
		{
			temp_copy[i][j] = ' ';
			temp_copy[i][j] = temp[i][j];
		}
	}
}
void Sudoku::set_difficulty(int number)
{
	difficulty = number;
}
//TO GENERATE SUDOKU FUNCTIONS
void Sudoku::converToChar()   //Function converting 2d vector to 2d array of char
{
	int count_x = 0;
	int count_y = 0;
	char c;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (((temp[i][j] >= '0') && (temp[i][j] <= '9')) || (temp[i][j] == '.'))
			{
				if (count_x == 9)
				{
					count_y++;
					count_x = 0;
					c = '0' + grid[count_y][count_x];
					temp[i][j] = c;
					count_x++;
				}
				else
				{
					c = '0' + grid[count_y][count_x];
					temp[i][j] = c;
					count_x++;
				}
			}
		}
	}
}
bool Sudoku::FindUnassignedLocation(int& row, int& col)   //Looking for unassigned element in 2d vector
{
	for (row = 0; row < GRIDY; row++)
		for (col = 0; col < GRIDY; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}
void Sudoku::convertToInt()   //Convert from 2d array of char to 2d vector
{
	int number = 0;
	int counter_x = 0;
	int counter_y = 0;
	char convertable = ' ';
	grid.resize(GRIDX, vector<int>(GRIDY));
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (((temp[i][j] >= '0') && (temp[i][j] <= '9')) || (temp[i][j] == '.'))
			{
				if (temp[i][j] == '.')
				{
					temp[i][j] = '0';
				}
				convertable = temp[i][j];
				number = (int)convertable - 48;
				if (counter_x == 9)
				{
					counter_y++;
					counter_x = 0;
					grid[counter_y][counter_x] = number;
				}
				else
				{
					grid[counter_y][counter_x] = number;
					counter_x++;
				}
			}
		}
	}
}
bool Sudoku::check()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j] == copy_grid[i][j])
				return true;
			else
				return false;
		}
	}
}
bool Sudoku::isSafe(int row, int col, int num)  //Checking if num can be placed in this location
{
	return (!UsedInRow(row, num)) && (!UsedInCol(col, num)) && (!UsedInBox(row - row % 3, col - col % 3, num)) && (grid[row][col] == UNASSIGNED);
}
bool Sudoku::UsedInCol(int col, int num)  //Checking if num is used in col
{
	for (int row = 0; row < 9; row++)
	{
		if (grid[row][col] == num)
			return true;
	}

	return false;

}
bool Sudoku::UsedInBox(int boxStartRow, int boxStartCol, int num) //Checking if number is used in box 3x3
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (grid[row + boxStartRow][col + boxStartCol] == num)
				return true;
		}
	}
	return false;
}
bool Sudoku::UsedInRow(int row, int num) //Checking if number is used in row
{
	for (int col = 0; col < 9; col++)
	{
		if (grid[row][col] == num)
			return true;
	}
	return false;
}
bool Sudoku::SolveSudoku()    //Function solving sudoku by backtracking algorithm
{
	int row, col;
	if (!FindUnassignedLocation(row, col))  //if there is no unassigned locations algorithm ends
		return true;

	for (int num = 1; num <= 9; num++)
	{
		if (isSafe(row, col, num))
		{
			grid[row][col] = num;
			if (SolveSudoku())     //checking if grid is solvable
				return true;

			grid[row][col] = UNASSIGNED;   //if element cant be placed in this place change location again to unassigned
		}
	}
	return false;
}
void Sudoku::CopyToOriginal()   //If 'K' is pressed and player want to see solved sudoku copy of solvation is copied to original grid
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grid[i][j] = copy_grid[i][j];
		}
	}
}
//----------------
void Sudoku::Copygrid()  //Making copy of solved grid
{
	copy_grid.resize(GRIDX, vector<int>(GRIDY));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			copy_grid[i][j] = grid[i][j];
		}
	}
}
void Sudoku::countSoln(int& number)  //counting possible solutions
{


	int row, col;
	if (!FindUnassignedLocation(row, col))
	{
		number++;
		return;
	}
	for (int i = 0; i < 9 && number < 2; i++)
	{
		if (isSafe(row, col, guessNum[i]))
		{
			grid[row][col] = guessNum[i];
			countSoln(number);
		}
		grid[row][col] = UNASSIGNED;
	}
}
void Sudoku::removeNum()  //Function removing elements from solved grid to randomize puzzle grid
{

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> randomer(0, 8);
	for (int i = 0; i < difficulty; i++)
	{
		int row = gridPos[i] / 9;
		int col = (gridPos[i]) % 9;
		if (grid[row][col] == 0)
		{
			row = randomer(rng);
			col = randomer(rng);
		}
		int temporar = grid[row][col];
		grid[row][col] = UNASSIGNED;
		int check = 0;
		countSoln(check);
		if (check != 1)
		{
			grid[row][col] = temporar;
		}
	}
}
//----------------------
//FUNCTION TO MOVE AND SAVE THE CHANGES IN GRID
void Sudoku::clearBox()
{
	HANDLE hOut;
	COORD Position;
	DWORD Written;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 10;
	FillConsoleOutputCharacter(hOut, ' ', 1000000, Position, &Written);

	SetConsoleCursorPosition(hOut, Position);
}
void Sudoku::print()
{

	clearBox(); //czysci buffor
	PlaceCursor(48, 6);
	_setmode(_fileno(stdout), _O_U16TEXT); //changing mode to print arrows
	wprintf(L"Movement : Up \x2191 , Down \x2193 , Left \x2190 , Right \x2192");
	PlaceCursor(36, 8);
	wcout << "To check sudoku press 'T' if you want see solved sudoku press 'K'";
	for (int i = 0; i < 13; i++)
	{
		PlaceCursor(57, 12 + i);
		for (int j = 0; j < 26; j++)
		{
			if ((temp_copy[i][j] == temp[i][j]) && (temp_copy[i][j] <= '9') && (temp_copy[i][j] >= '1'))
			{
				HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(color, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				wcout << temp[i][j];
				SetConsoleTextAttribute(color, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
				wcout << temp[i][j];

		}

	}

}
void Sudoku::move(int V, int H)   //moving in the char grid
{
	int y2 = y + V;
	int x2 = x + H;
	if (x != x2)
	{

		char k = temp[y][x2];
		if ((temp[y][x2] >= 48) && (temp[y][x2] <= 57))
		{
			helper.push(k);
			x += H;
			temp[y][x] = '.';
			if (temp[y][x2 - H] == '.')
			{
				temp[y][x2 - H] = helper.front();
				helper.pop();

			}
		}
		//ADDED---------------------
		if ((temp[y][x2] == '|') || (temp[y][x2] == '='))
		{
			//RIGHT
			if (H > 0)
			{
				helper.push(temp[y][x2 + 2]);
				H += 2;
				x += H;
				temp[y][x] = '.';
				if (temp[y][(x2 + 2) - H] == '.')
				{
					temp[y][(x2 + 2) - H] = helper.front();
					helper.pop();

				}
			}
			//LEFT
			if (H < 0)
			{
				helper.push(temp[y][x2 - 2]);
				H -= 2;
				x += H;
				temp[y][x] = '.';
				if (temp[y][(x2 - 2) - H] == '.')
				{
					temp[y][(x2 - 2) - H] = helper.front();
					helper.pop();

				}

			}
		}
		//------------------------
	}
	if (y != y2)
	{
		char k = temp[y2][x];
		if ((temp[y2][x] >= 48) && (temp[y2][x] <= 57))
		{
			helper.push(k);
			y += V;
			temp[y][x] = '.';

			if (temp[y2 - V][x] == '.')
			{
				temp[y2 - V][x] = helper.front();
				helper.pop();
			}
		}
		//ADD---------------------------
		if ((temp[y2][x] == '|') || (temp[y2][x] == '='))
		{
			//RIGHT
			if (V > 0)
			{
				helper.push(temp[y2 + 1][x]);
				V += 1;
				y += V;
				temp[y][x] = '.';

				if (temp[(y2 + 1) - V][x] == '.')
				{
					temp[(y2 + 1) - V][x] = helper.front();
					helper.pop();
				}
			}
			//LEFT
			if (V < 0)
			{
				helper.push(temp[y2 - 1][x]);
				V -= 1;
				y += V;
				temp[y][x] = '.';

				if (temp[(y2 - 1) - V][x] == '.')
				{
					temp[(y2 - 1) - V][x] = helper.front();
					helper.pop();
				}
			}
		}
	}

}
void Sudoku::reverseQueue(queue<char>& Queue)
{
	stack<char> Stack;
	while (!Queue.empty()) {
		Stack.push(Queue.front());
		Queue.pop();
	}
	while (!Stack.empty()) {
		Queue.push(Stack.top());
		Stack.pop();
	}
}
void Sudoku::put(char number)
{
	temp[y][x] = number;
	reverseQueue(helper);   //deleting of last element of the queue because last element is double after put function
	helper.pop();
	reverseQueue(helper);
}
