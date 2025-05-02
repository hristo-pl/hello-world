#include <stdio.h>

void print_row(int rows, int row_i, int *arr_cur, int *arr_prev) {
    for (int j = 0; j < rows + row_i; j++) {
        //assigns 0 and prints spaces before the first '1' in the row.
        if (j < rows - row_i - 1) {
            printf(" ");
            continue;
        //prints the first '1'
        } else if (j == rows - row_i - 1) {
            arr_cur[j] = 1;
            printf("%d", arr_cur[j]);
            if (row_i == 0) {
                break;
            }
            printf(" ");
            continue;
        // assigns '1' and finish printing the row with '1'.
        } else if (j == rows - 1) {
            arr_cur[j] = 1;
            printf("%d", arr_cur[j]);
            break;
        // fill the numbers between first and second '1'
        } else {
            arr_cur[j] = arr_prev[j] + arr_prev[j + 1];
            printf("%d", arr_cur[j]);
            printf(" ");
            continue;
        }
    }
}

void print_pascals_triangle(int rows) {
    int arr_even[rows] = {};
    int arr_odd[rows] = {};
    
    for (int row_i = 0; row_i < rows; row_i++) {
        if (row_i % 2 == 0) {
            print_row(rows, row_i, arr_even, arr_odd);
        }
        else {
            print_row(rows, row_i, arr_odd, arr_even);
        }
        printf("\n");
    }
}

int main() {
    int rows;
    scanf("%d", &rows);
    
    print_pascals_triangle(rows);
    
    return 0;
}