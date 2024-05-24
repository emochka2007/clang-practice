#include <ncurses.h>
#include <time.h>
#include <stdlib.h>


int max_buffer_len = 0;

int snake_len = 0;
int random_x = 0;
int random_y = 0;
int start_snake =0;


void gen_rand_yx()
{
	random_x = rand() % 5;
	random_y = rand() % 25;
}
void spawn_apple(int x, int y)
{
	char *apple = "+";
	mvaddstr(y, x, apple);
}

void print_array(int *arr, int len, char *comment)
{
	printw("Array %s:\n", comment);
	for (int i = 0; i < len; i++)
	{
		printw("%d ", arr[i]);
	}
	printw("\n");
}

void print_snake(int *cell_x_coord, int* cell_y_coord,char* snake_cell){
    
		if(start_snake<=snake_len) {
		for(int i=start_snake; i<snake_len; i++){
	    mvaddstr(cell_y_coord[i], cell_x_coord[i], snake_cell);
}
} else {
	 for(int i=start_snake; i<max_buffer_len;i++) {
	     mvaddstr(cell_y_coord[i], cell_x_coord[i], snake_cell);
	    }
	for (int i=0; i<snake_len;i++){
	     mvaddstr(cell_y_coord[i], cell_x_coord[i], snake_cell);
}} 

}

void move_to_left(int *x_arr, int *y_arr)
{
	start_snake++;
	if(start_snake >= max_buffer_len){
	start_snake = 0;
}
}


void grow(int *x_arr, int *y_arr, int x, int y)
{	y_arr[snake_len] = y;
	x_arr[snake_len] = x;
	snake_len++;
	if(snake_len >= max_buffer_len){
	snake_len = 0;
    }
}

int is_intersected(int *x_arr, int *y_arr, int arr_len, int head_x, int head_y)
{
	for (int i = arr_len - 2; i >= 0; i--)
	{
		if (x_arr[i] == head_x && y_arr[i] == head_y)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{

	initscr();
	srand(time(NULL));

	int y = 10;
	int x = 10;
	char *snake_cell = "*";

	mvaddstr(y, x, snake_cell);
	int max_y = 0;
	int max_x = 0;
	getmaxyx(stdscr, max_y, max_x);
	int cell_y_coord[max_y * max_x];
	int cell_x_coord[max_y * max_x];
	max_buffer_len = 7;
	grow(cell_x_coord, cell_y_coord, 10, 10);
	// halfdelay(3);
	int direction = 'L';
	gen_rand_yx();
	while (1)
	{
		int code = getch();
		switch (code)
		{
		case 97:
			if (direction != 'R')
			{
				direction = 'L';
			}
			break;
		case 115:
			if (direction != 'D')
			{
				direction = 'U';
			}
			break;
		case 100:
			if (direction != 'L')
			{
				direction = 'R';
			}
			break;
		case 119:
			if (direction != 'U')
			{
				direction = 'D';
			}
			break;
		}
		halfdelay(2);

		switch (direction)
		{
		case 'L':
			x--;
			break;
		case 'U':
			y++;
			break;
		case 'R':
			x++;
			break;
		case 'D':
			y--;
			break;
		}
		grow(cell_x_coord, cell_y_coord, x, y);
		erase();

		// printw("%d snake_len\n", snake_len);
		if (y == random_y && x == random_x)
		{

			gen_rand_yx();
		}
		else
		{
			move_to_left(cell_x_coord, cell_y_coord);
		}
		int head_x = cell_x_coord[snake_len - 1];
		int head_y = cell_y_coord[snake_len - 1];
		print_snake(cell_x_coord, cell_y_coord,snake_cell); 
		

		spawn_apple(random_x, random_y);
	}
	endwin();
	return 0;
}