#include<iostream>
#include"poker.h"
#include<time.h>

using namespace std;

int main()
{
	srand(time(NULL));
	system("mode con cols=150 lines=70");
	int total_have[14][14] = { 0 };
	int first;
	int played_max[5] = { 7 };
	int played_min[5] = { 7 };
	game player ,computer;
	player.deal(& **total_have);
	computer.deal(& **total_have);
	player.begin(& **total_have, & first);
	computer.com_begin(& **total_have, & first);
	player.print_card();
	if (first == 2)
	{
		while (player.get_count() != 0 || computer.get_count() != 0)
		{
			player.play(&**total_have, &*played_max, &*played_min);
			player.erase_card();
			player.print_card();
			computer.computer(&**total_have, &*played_max, &*played_min);
		}
	}
	else
	{
		while (player.get_count() != 0 || computer.get_count() != 0)
		{
			computer.computer(&**total_have, &*played_max, &*played_min);
			player.play(&**total_have, &*played_max, &*played_min);
			player.erase_card();
			player.print_card();
		}
	}
	
	if (player.get_fold_point() < computer.get_fold_point())
	{
		for (int i = 0; i < 10; i++)
		{
			cout << "You win!!!!               " << endl;
		}
	}
	else if (player.get_fold_point() > computer.get_fold_point())
	{
		for (int i = 0; i < 10; i++)
		{
			cout << "You Lose!!!               " << endl;
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			cout << "Tie                       " << endl;
		}
	}
	
	while (1);
}  