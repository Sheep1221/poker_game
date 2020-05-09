#include<iostream>
#include<time.h>
#include "poker.h"
#include<Windows.h>

using namespace std;

void game::deal(int* total_have)
{ 
	int r=0, c=0;
	for (int i = 0; i < 26; i++)
	{
		do {
			// randomly draw card
			number = (rand() % 13) + 1;
			suit = (rand() % 4) + 1;
			// judge repeat or not
		} while (total_have[number * 14 + suit] != 0);
		have_card[number][suit] = 1;
		total_have[number*14+suit] = 1;
	}
}

void game::game_appear(int c, int r)
{
	for (int i = 0; i <= row; i++)
	{
		gotoxy(c * 10, 3 + 3 * 13 + r+i); //set the position of card printing
		for (int j = 0; j <= col; j++)
		{

			if (suit == 1 || suit == 4)//set color of card
				setcolor(0, 7); //0=black, 7=white
			else
				setcolor(4, 7); //4=red
			cout << looking[i][j];
			setcolor(7, 0);
		}
		cout << endl;
	}
}

void game::com_begin(int* total_have, int* first)
{

	if (have_card[7][4] == 1)
	{
		*first = 2;
		have_card[7][4] = 0;
		total_have[number * 14 + suit] = 0;
		number = 7;
		suit = 4;
		make_card();
		appear(4, 1);
		count--;
	}
	
}

void game::begin(int* total_have, int* first)
{
	if (have_card[7][4] == 1)
	{
		*first = 1;
		have_card[7][4] = 0;
		total_have[number * 14 + suit] = 0;
		number = 7;
		suit = 4;
		make_card();
		appear(4, 1);
		pos_c = 1;
		count--;
	}
}

void game::erase_card()
{
	if (pos_c > 12)
	{
		pos_c = 0;
		pos_r++;
	}
	for (int i = 0; i <= row; i++)
	{
		gotoxy((12-pos_c) * 10, 3 + 3 * 13 + 8*(1-pos_r) + i); //set the position of card printing
		for (int j = 0; j <= col; j++)
		{
			setcolor(0, 0);
			cout << looking[i][j];
			setcolor(7, 0);
		}
		cout << endl;
	}
	pos_c++;
}

void game::print_card()
{
	int r = 0, c = 0;
	for (int i = 1; i <= 13; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (have_card[i][j] == 1)
			{
				number = i;
				suit = j;
				make_card();
				game_appear(c, r);
				c += 1;
				if (c % 13 == 0)
				{
					r += 8;
					c = 0;
				}
			}
		}
	}
}

void game::play(int* total_have, int* played_max, int*played_min)
{
	for (int i = 1; i <= 4; i++)
	{
		if (have_card[played_max[i] - 1][i] == 1)
			can_play = true;
		 else if (have_card[played_min[i] + 1][i] == 1)
			can_play = true;
		else if (have_card[7][i] == 1)
			can_play = true;
	}
	if (!can_play)
	{
		cout << "Sorry, you have no card avalible, please fold a card!!!" << endl;
	}
	else
		cout << "                                                        " << endl;
	game_input(total_have);
	if (can_play)
	{
		make_card();
		if (number == 7)
			appear(suit, 1);
		else if (number > 7)
		{
			appear(suit, 0);
			played_min[suit] = number;
		}
		else if (number < 7)
		{
			appear(suit, 2);
			played_max[suit] = number;
		}
		total_have[number * 14 + suit] = 0;
	}
	if (!can_play)
	{
		total_have[number * 14 + suit] = 2;
		fold_point += number;
	}
	have_card[number][suit] = 0;
	can_play = false;
	count--;
}

void game::game_input(int* total_have)
{
	char sui;
	bool sui_bool = false, num_bool = false;
	gotoxy(0, 62);
	do
	{
		if (have_card[number][suit] != 1)
			cout << "You don't have this card!!!,please input again." << endl;
		cout << "Please key the card you want to use(value in number, suit in c, d, h, s):";
		cin >> number >> sui;
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
		}
		if (1 <= number && number <= 13)num_bool = true;
		unused_seven = false;
		unused_card = false;
		if (number != 7)
		{
			if (have_card[7][1] == 1 || have_card[7][2] == 1 || have_card[7][3] == 1)
			{
				cout << "plese use 7 first!!!" << endl;
				unused_seven = true;
			}
		}
		if (number > 7)
		{
			for (int i = 8; i < number; i++)
			{
				if (total_have[i * 14 + suit] == 1)
				{
					unused_card = true;
				}
			}
			if (unused_card == true)
			{
				cout << "Can't use this card without smaller card!!!" << endl;
			}
		}
		else if (number < 7)
		{
			for (int i = 6; i > number; i--)
			{
				if (total_have[i * 14 + suit] == 1)
				{
					unused_card = true;
				}
			}
			if (unused_card == true)
			{
				cout << "Can't use this card without bigger card!!!" << endl;
			}
		}
	} while (!sui_bool||!num_bool||have_card[number][suit] != 1||unused_seven||unused_card);
	make_card();
}

void game::computer(int* total_have, int* played_max, int* played_min)
{
	for (int i = 1; i <= 4; i++)
	{
		if (have_card[played_max[i] - 1][i] == 1)
			can_play = true;
		else if (have_card[played_min[i] + 1][i] == 1)
			can_play = true;
		else if (have_card[7][i] == 1)
			can_play = true;
	}
	if (!can_play)
	{
		cout << "computer fold a card!!!!";
	}
	if (have_card[7][1] == 1)
	{
		number = 7;
		suit = 1;
	}
	else if (have_card[7][2] == 1)
	{
		number = 7;
		suit = 2;
	}
	else if (have_card[7][3] == 1)
	{
		number = 7;
		suit = 3;
	}
	else 
	{
		do {
			// randomly draw card
			number = (rand() % 13) + 1;
			suit = (rand() % 4) + 1;
			// judge repeat or not
			unused_card = false;
			if (number > 7)
			{
				for (int i = 8; i < number; i++)
				{
					if (total_have[i * 14 + suit] != 0)
					{
						unused_card = true;
					}
				}
			}
			else if (number < 7)
			{
				for (int i = 6; i > number; i--)
				{
					if (total_have[i * 14 + suit] != 0)
					{
						unused_card = true;
					}
				}
			}

		} while (have_card[number][suit] == 1 || unused_card);
	}
	if (can_play)
	{
		make_card();
		if (number == 7)
			appear(suit, 1);
		else if (number > 7)
		{
			appear(suit, 0);
			played_min[suit] = number;
		}
		else if (number < 7)
		{
			appear(suit, 2);
			played_max[suit] = number;
		}
		total_have[number * 14 + suit] = 0;
	}
	if (!can_play)
	{
		total_have[number * 14 + suit] = 2;
		fold_point += number;
	}
	have_card[number][suit] = 0;
	can_play = false;
	count--;
}

int game::get_count()
{
	return count;
}

int game::get_fold_point()
{
	return fold_point;
}
