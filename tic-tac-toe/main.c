#include <stdio.h>
#include <stdlib.h>

typedef struct BoardNode
{
    struct BoardNode *next;
    char board[3][3];

} BoardNode;
void print_ttt(char arr[3][3])
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("| %c", arr[i][j]);
        }
        printf("\n");
    }
}

void print_list(struct BoardNode *list)
{
    while (list != NULL)
    {
        print_ttt(list->board);
        list = list->next;
    }
}
struct BoardNode *add_value_to_list_start(char arr[3][3], struct BoardNode *list)
{
    struct BoardNode *new_node = malloc(sizeof(struct BoardNode));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            new_node->board[i][j] = arr[i][j];
        }
    }
    new_node->next = list;
    return new_node;
}

char get_winner(char arr[3][3])
{
    char winner = '_';
    for (int row = 0; row < 3; row++)
    {
        if (arr[row][0] == arr[row][1] && arr[row][1] == arr[row][2])
        {
            return arr[row][0];
        }
        if (arr[row][0] == arr[1][row] && arr[1][row] == arr[2][row])
        {
            return arr[row][0];
        }
        if (arr[row][0] == arr[1][1] && arr[1][1] == arr[2][2])
        {
            return arr[row][0];
        }
        if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])
        {
            return arr[0][2];
        }

        // для столбиков и перекрестья проверку
        // лишний вывод столбика пустого
        // инпут от 1 до 9, с командной строки брать символ и число, scanf()
        // алгоритм мини макс
    }
    return winner;
}

BoardNode *print_possible_steps(char arr[3][3], char symbol)
{
    struct BoardNode *new_node = malloc(sizeof(struct BoardNode));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == '_')
            {
                arr[i][j] = symbol;
                new_node = add_value_to_list_start(arr, new_node);
                print_ttt(arr);
                printf("\n\n");
                arr[i][j] = '_';
            }
        }
    }
    return new_node;
}

void insert_into_board(char arr[3][3], int coord)
{
    coord--;
    int row = coord / 3;
    int col = coord % 3;

    arr[row][col] = 'X';
}

int main()
{
    char ttt_arr[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};
    int users_choice = 0;

    printf("Enter your coord from 1 to 9: ");
    scanf("%d", &users_choice);

    if (users_choice < 1 || users_choice > 9)
    {
        abort();
    }
    else
    {
        insert_into_board(ttt_arr, 3);
        insert_into_board(ttt_arr, 1);
        insert_into_board(ttt_arr, 4);
    }
    print_ttt(ttt_arr);
    // char winner = get_winner(ttt_arr);
    // printf("%c\n", winner);
    // BoardNode *result = print_possible_steps(ttt_arr, 'Z');
    // print_list(result);

    return 0;
}