#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
int *gen_rand_yx(int max_x, int max_y)
{
	int random_x = rand() % 25;
	int random_y = rand() % 25;
	int *rand_arr = (int *)malloc(2 * sizeof(int));
	rand_arr[0] = random_x;
	rand_arr[1] = random_y;
	return rand_arr;
}
void spawn_apple(int y, int x)
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

int *move_to_left(int *arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		arr[i - 1] = arr[i];
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
	int snake_len = 1;
	int *apple_coords = gen_rand_yx(max_y, max_x);
	while (1)
	{
		int code = getch();
		switch (code)
		{
		case 97:
			x--;
			break;
		case 115:
			y++;
			break;
		case 100:
			x++;
			break;
		case 119:
			y--;
			break;
		}
		cell_y_coord[snake_len - 1] = y;

		cell_x_coord[snake_len - 1] = x;

		erase();
		print_array(cell_y_coord, snake_len, " Y ");
		print_array(cell_x_coord, snake_len, " X ");
		printw("%d snake_len\n", snake_len);
		if (y == apple_coords[0] && x == apple_coords[1])
		{
			snake_len++;
			apple_coords = gen_rand_yx(max_y, max_x);
		}
		else
		{
			move_to_left(cell_x_coord, snake_len);
			move_to_left(cell_y_coord, snake_len);
		}
		for (int i = 0; i < snake_len; i++)
		{
			printw("%d scell_y_coord[i]\n", cell_y_coord[i]);
			mvaddstr(cell_y_coord[i], cell_x_coord[i], snake_cell);
		}
		spawn_apple(apple_coords[0], apple_coords[1]);
	}
	endwin();
	return 0;
}
