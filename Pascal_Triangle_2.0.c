#include <stdio.h>

void print_pascals_triangle(int rows) {
    int arr_cur[rows] = {};
    int arr_prev[rows] = {};
    
    for (int row_i = 0; row_i < rows; row_i++) {
        // prints white spaces for alignment
		for ( int spaces = 0; spaces < rows - row_i - 1; spaces++) {
			printf(" ");
		}
		// prints one row
		for (int j = 0; j <= row_i; j++) {
			// prints the last '1' of the row
			if (j == row_i) {
				arr_cur[j] = 1;
				printf("%d", arr_cur[j]);
			// prints the first '1' of the row
			} else if (j == 0) {
				arr_cur[j] = 1;
				printf("%d", arr_cur[j]);
				printf(" ");
			// fill the numbers between first and second '1'
			} else {
				arr_cur[j] = arr_prev[j] + arr_prev[j - 1];
				printf("%d", arr_cur[j]);
				printf(" ");
			}
		}
		 // transfers the values from curr to prev array
        for (int j = 0; j <= row_i; j++) {
			arr_prev[j] = arr_cur[j];
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