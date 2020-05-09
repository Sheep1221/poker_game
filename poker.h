#define MAX_row 12
#define MAX_col 15

void gotoxy(int , int );
void setcolor(int , int );

class card
{
public:
	void get_number();
	void get_suit();
	void make_card();
	void appear(int , int );
	void get_rand(int);
	
protected:
	int number;
	int suit;
	char looking[MAX_row][MAX_col] = {' '}; //set the size of card
	const int row = MAX_row - 1, col = MAX_col-1;
	int have_card[14][5] = {0}; // record weather the card used or not
	int row_record=0; //record the row that we need to print at next loop

};

class game  : public card
{public:
	void deal(int*);
	void begin(int*, int*);
	void com_begin(int*, int*);
	void game_appear(int, int);
	void erase_card();
	void print_card();
	void play(int*, int*, int*);
	void game_input(int*);
	void computer(int *, int*, int*);
	int get_count();
	int get_fold_point();

protected:
	bool unused_seven = false;
	bool unused_card = false;
	int fold_point = 0;
	bool can_play = false;
	int pos_r = 0;
	int pos_c = 0;
	int fold_time = 0;
	int count = 26;
};


