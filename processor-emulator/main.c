#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
void fill_with_zeros(char *bin, int len);
void sum_two_bin(char *a, char *b, char sum[]);
void mult_by_digit(char mul[], int value, char res[]);
void left_shift_bin(char bin[], int offset);
int mult_two_bin(char bin1[], char bin2[], char res[])
{
    assert(strlen(bin1) == strlen(bin2));
    char sum[strlen(bin1)];

    fill_with_zeros(sum, strlen(bin1));
    for (int i = 0; i < strlen(bin2); i++)
    {
        char mult_res[strlen(bin1)];
        fill_with_zeros(mult_res, strlen(bin1));
        mult_by_digit(bin1, bin2[i] - '0', mult_res);
        left_shift_bin(mult_res, i);
        sum_two_bin(mult_res, sum, sum);
    }
}
void fill_with_zeros(char *bin, int len)
{
    // int count = sizeof(array) / sizeof(array[0]);
    // arr[i]  == *(arr+i)
    // arr[0] == *(arr+0) == *arr

    for (int i = 0; i < len; i++)
    {
        bin[i] = '0';
    }
    bin[len] = '\0';
}

void mult_by_digit(char mul[], int value, char res[])
{
    // 1010 * 0 = 1010
    //        101
    //      x  11
    //     ------
    //        101   <- This is 101 multiplied by 1 (rightmost bit of 11)
    // +    1010   <- This is 101 multiplied by 1 (left bit of 11), shifted left by one position
    //     ------
    //     11111
    int mul_len = strlen(mul);
    for (int i = 0; i < mul_len; i++)
    {
        int prod = (mul[i] - '0') * value;
        res[i] = prod + '0';
    }
}

void left_shift_bin(char bin[], int offset)
{
    int bin_len = strlen(bin);

    for (int i = 0; i < bin_len - offset; i++)
    {
        bin[i] = bin[i + offset];
    }
    for (int i = 0; i < offset; i++)
    {
        bin[bin_len - 1 - i] = '0';
    }
}

// n **m = n * n * ... * n-- - V-- -- -m
// calculate the power of a:
int to_power(int num, int power)
{

    if (power == 0)
    {
        return 1;
    }

    return num * to_power(num, power - 1);
}
void int_to_bin(int num, int len, char res[])
{
    // 10 -> 10 % 2 -> 5%2->2%2->1%2=1
    //       0-1-0-1 (1010)
    for (int i = len - 1; i >= 0 && num > 0; i--)
    {
        int bin = num % 2;
        num = num / 2;
        res[i] = bin + '0';
    }
    res[len] = '\0';
}

int bin_to_int(char *bin)
{
    int bin_len = strlen(bin);
    int res = 0;
    // 2 ^ 0 + 2 ^ 1 * 1 + 2 ^ 2 * 0 + 2 ^ 3 * 1
    int power = 0;
    for (int i = bin_len - 1; i >= 0; i--)
    {
        int bin_int = bin[i] - '0';
        res += to_power(2, power) * bin_int;
        power++;
    }
    return res;
}
void sum_two_bin(char *a, char *b, char sum[])
{
    int a_len = strlen(a);
    int b_len = strlen(b);
    printf("a, %s\n", a);
    printf("b, %s\n", b);
    if (a_len != b_len)
    {
        printf("Error in sum_two_bin, diff in lengths");
        exit(1);
    }
    int carry = 0;
    for (int i = a_len - 1; i >= 0; i--)
    {
        int internal_sum = a[i] - '0' + b[i] - '0' + carry;
        carry = 0;
        if (internal_sum == 2)
        {
            carry = 1;
            internal_sum = 0;
        }
        sum[i] = internal_sum + '0';
    }
    sum[a_len] = '\0';
}

void get_bits_from_instruction(int start, int end, char *result, char *cell)
{
    for (int i = start, j = 0; i < end; i++, j++)
    {
        result[j] = cell[i];
    }
}
int main()
{

    // char binary_sum[] = "00101010"; // 010110
    // char int_to_bin[] = "00000101";
    // char binary_mul[] = "00000000";
    // mult_two_bin(binary_sum, int_to_bin, binary_mul);
    char operation_field[] = "0000";
    char instruction_cell[] = "1000100010001000";
    get_bits_from_instruction(12, 16, operation_field, instruction_cell);
    printf("%s oper", operation_field);
    return 0;
}
