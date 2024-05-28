#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

int snake_len = 0;
int random_x = 0;
int random_y = 0;
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

void move_to_left(int *x_arr, int *y_arr)
{
	for (int i = 1; i < snake_len; i++)
	{
		x_arr[i - 1] = x_arr[i];
		y_arr[i - 1] = y_arr[i];
	}

	snake_len--;
}

void grow(int *x_arr, int *y_arr, int x, int y)
{
	y_arr[snake_len] = y;
	x_arr[snake_len] = x;
	snake_len++;
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
		print_array(cell_y_coord, snake_len, " Y ");
		print_array(cell_x_coord, snake_len, " X ");

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

		if (is_intersected(cell_x_coord, cell_y_coord, snake_len, head_x, head_y))
		{

			endwin();
			return 0;
		}

		for (int i = 0; i < snake_len; i++)
		{

			mvaddstr(cell_y_coord[i], cell_x_coord[i], snake_cell);
		}

		spawn_apple(random_x, random_y);
	}
	endwin();
	return 0;
}