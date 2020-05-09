#include<iostream>
#include<Windows.h>
#include<time.h>
#include "poker.h"

using namespace std;

void gotoxy(int xpos, int ypos)//set position
{
	COORD scrn;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOut, scrn);
}

void setcolor(int f = 7, int b = 0)
{	// first variable is text color
	// second variable is background color
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

void card::get_number()
{
	int num;
	bool num_bool = false;
	while (!num_bool)
	{
		//gotoxy(0, 25);
		cout << "----------------------------------------------" << endl;
		cout << "Please enter the number in digit:";
		cin >> num;
		if (num >= 1 && num <= 13)
		{
			number = num;
			num_bool = true;
		}
		else
			cerr << "wrong number!!!"<< endl;
	}
	
}

void card::get_suit()
{
	char sui;
	bool sui_bool=false;
	while (!sui_bool)
	{
		//gotoxy(0, 27);
		cout << "Please enter the suit:" << endl;;
		cout << "club = c" << endl;
		cout << "diomond = d " << endl;
		cout << "heart = h" << endl;
		cout << "spade = s" << endl;
		cin >> sui;
		switch (sui)
		{
		case 'c': //club
			suit = 1;
			sui_bool = true;
			break;
		case 'd': //diamond
			suit = 2;
			sui_bool = true;
			break;
		case 'h': //heart
			suit = 3;
			sui_bool = true;
			break;
		case 's': //spade
			suit = 4;
			sui_bool = true;
			break;
		default:
			cout << "wrong suit!!!" << endl;
	}
	}
	
}

void card::make_card()
{

#pragma region shape
	memset(looking, ' ', sizeof(looking));
	for(int i= 0; i<= row; i++)
	{
		looking[i][0] = '|';
		looking[i][col] = '|';
	}
	for (int j = 0; j <= col; j++)
	{
		looking[0][j] = '=';
		looking[row][j] = '=';
	}

#pragma endregion

#pragma region number
	if (number < 10)
	{
		looking[0][0] = '1'-1+ number;
		looking[row][col] = '1'-1+ number;
	}
	else if (number == 10)
	{
		looking[0][0] = '1';
		looking[0][1] = '0';
		looking[row][col-1] = '1';
		looking[row][col] = '0';
	}
	else
	{
		switch (number)
		{
		case 11:
			looking[0][0] = 'J';
			looking[row][col] = 'J';
			break;
		case 12:
			looking[0][0] = 'Q';
			looking[row][col] = 'Q';
			break;
		case 13:
			looking[0][0] = 'K';
			looking[row][col] = 'K';
			break;

		}
	}
#pragma endregion

#pragma region suit
	switch (suit)
	{
#pragma region club
	case 1:
		for (int i = 2; i <= 9; i++)
		{
			looking[i][col / 2] = '*';
		}

		for (int j = col / 2 - 1; j <= col / 2 + 1; j++)
		{
			looking[3][j] = '*';
		}

		for (int j = col / 2 - 4; j <= col / 2 + 4; j++)
		{
			looking[6][j] = '*';
		}

		for (int i = 5; i <= 7; i++)
		{
			for (int j = col / 2 - 3; j <= col / 2 - 2; j++)
				looking[i][j] = '*';
		}

		for (int i = 5; i <= 7; i++)
		{
			for (int j = col / 2 + 2; j <= col / 2 + 3; j++)
				looking[i][j] = '*';
		}
		looking[8][col / 2 - 3] = '*';
		looking[8][col / 2 + 3] = '*';
		break;
#pragma endregion

#pragma region diaomnd
	case 2:
		for (int i = 2; i <= 6; i++)
		{
			for (int j = col / 2 - i + 2; j <= col / 2 + i - 2; j++)
			{
				looking[i][j] = '*';
			}
		}
		for (int i = 7; i <= 10; i++)
		{
			for (int j = col / 2 + i - 10; j <= col / 2 - i + 10; j++)
			{
				looking[i][j] = '*';
			}
		}
		break;
#pragma endregion

#pragma region heart
	case 3:
		for (int i = 5; i <= 9; i++)
		{
			for (int j = col / 2 + i - 9; j <= col / 2 - i + 9; j++)
			{
				looking[i][j] = '*';
			}
		}
		for (int i = 2; i <= 4; i++)
		{
			for (int j = col / 2 - 4; j <= col / 2 + 4; j++)
			{
				looking[i][j] = '*';
			}
		}
		for (int j = col / 2 - 1; j <= col / 2 + 1; j++)
		{
			looking[2][j] = ' ';
		}
		looking[3][col / 2] = ' ';
		looking[2][col / 2-4] = ' ';
		looking[2][col / 2+4] = ' ';
		break;
#pragma endregion

#pragma region spade
	case 4:
		for (int i = 2; i <= 9; i++)
		{
			looking[i][col / 2] = '*';
		}
		for (int i = 3; i <= 6; i++)
		{
			looking[i][col / 2 + 1] = '*';
			looking[i][col / 2 - 1] = '*';
		}
		for (int i = 4; i <= 6; i++)
		{
			looking[i][col / 2 + 2] = '*';
			looking[i][col / 2 - 2] = '*';
		}
		for (int i = 5; i <= 6; i++)
		{
			looking[i][col / 2 + 3] = '*';
			looking[i][col / 2 - 3] = '*';
		}
		break;
#pragma endregion
	}
#pragma endregion

}

void card::appear(int c, int r)
{
	for (int i = 0; i <= row; i++)
	{
		gotoxy(c*17, 3+r*13+i); //set the position of card printing
		for (int j = 0; j <= col; j++)
		{
		
			if (suit == 1 || suit == 4)//set color of card
				setcolor(0, 7); //0=black, 7=white
			else
				setcolor(4, 7); //4=red
			cout << looking[i][j];
			setcolor();
		}
		cout << endl;
	}
}

void card::get_rand(int rand_num)
{
	int r, c;
	for (int i = 0; i < rand_num; i++)
	{
		do {
			// randomly draw card
			number = (rand() % 13)+1; 
			suit = (rand() % 4)+1;
			// judge repeat or not
		} while (have_card[number][suit] != 0);
		have_card[number][suit] = 1;
		make_card();
		r = i / 5+row_record; c = i % 5;
		appear(c, r);
	}
	row_record = r+1;
}

