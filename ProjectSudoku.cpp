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
#include "Sudoku.h"
#define UNASSIGNED 0
#define GRX 13
#define GRY 26
#define GRIDX 9
#define GRIDY 9
using namespace std;
void colorchange()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
int setlocation(string n1, string n2) //centering text to menu
{
	return (n1.length() / 2) - (n2.length() / 2);
}
int difficulty_menu()
{
	int path;
	PlaceCursor(60, 10);
	string go = "Choose difficulty level:";
	string go1 = "1.Easy";
	string go2 = "2.Medium";
	string go3 = "3.Hard";
	cout << go;
	PlaceCursor(60 + setlocation(go, go1), 12);
	cout << go1;
	PlaceCursor(60 + setlocation(go, go2), 14);
	cout << go2;
	PlaceCursor(60 + setlocation(go, go3), 16);
	cout << go3;
	PlaceCursor(60 + go.length() / 2, 18);
	cin >> path;
	switch (path)
	{
	case 1:
	{
		int difficultylvl = 50;
		return difficultylvl;
	}
	break;
	case 2:
	{
		int difficultylvl = 65;
		return difficultylvl;
	}
	break;
	case 3:
	{
		int difficultylvl = 81;
		return difficultylvl;
	}
	break;
	}
}
int menu()
{
	int path;
	string instru = "Welcome in Sudoku:";
	string newgame = "1.New Game";
	string exit = "2.Exit";
	PlaceCursor(60, 10);
	cout << instru;
	PlaceCursor(60 + setlocation(instru, newgame), 12);
	cout << newgame;
	PlaceCursor(60 + setlocation(instru, exit), 14);
	cout << exit << endl;
	PlaceCursor(60 + instru.length() / 2, 16);
	cin >> path;
	switch (path)
	{
	case 1:
	{
		system("cls");
		int k = difficulty_menu();
		Sleep(1000);
		return k;
	}
	break;
	case 2:
	{
		string game2 = "I see you would like to exit";
		PlaceCursor(60 + setlocation(instru, game2), 18);
		cout << game2;
		Sleep(3000);
		return 0;
	}
	break;
	default:
	{
		string wrong = "Wrong option choosen";
		PlaceCursor(60 + setlocation(instru, wrong), 18);
		cout << wrong;
		Sleep(3000);
		return 0;
	}
	}
}
int main()
{
	bool gamerunning = true;
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1200, 600, TRUE);
	// Window resizeing
	colorchange();
	int difficulty = menu();
	if (difficulty == 0)
	{
		return 0;
	}
	Sudoku gamer;
	gamer.set_difficulty(difficulty);
	gamer.SolveSudoku();
	gamer.Copygrid();
	gamer.converToChar();  //*
	gamer.temporary_copy(); //*
	gamer.removeNum();
	gamer.converToChar();
	//gamer.temporary_copy();
	gamer.print();
	bool game = true;
	char key;
	do
	{
		gamer.clearBox();
		gamer.print();
		system("pause>nul");
		if (GetAsyncKeyState(VK_UP))
		{
			gamer.move(-1, 0);
			gamer.print();
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			gamer.move(1, 0);
			gamer.print();
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			gamer.move(0, -2);
			gamer.print();
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			gamer.move(0, 2);
			gamer.print();
		}
		key = getchar();
		if ((key >= 48) && (key <= 57))
		{
			gamer.put(key);
		}
		if (key == 'k')
		{
			gamer.convertToInt();
			gamer.CopyToOriginal();
			gamer.converToChar();
			gamer.print();
		}
		if (key == 't')
		{
			gamer.convertToInt();
			if (gamer.check())
			{
				PlaceCursor(56, 30);
				wcout << "You solved sudoku correctly";
			}
			else
			{
				PlaceCursor(55, 30);
				wcout << "You solved sudoku uncorrectly";
			}
			Sleep(10000);
			break;
			
		}

	} while (game);

	cin.ignore();
	cin.get();

	return 0;
}

