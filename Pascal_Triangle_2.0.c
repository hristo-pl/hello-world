#include <stdio.h>

void print_pascals_triangle(int rows) {
    int values[rows] = {};
    
    for (int row = 0; row < rows; row++) {
		for (int i = 0; i < rows - row -1; i++) { // Print white space.
			printf(" ");
		}
		values[0] = 1;
		printf("%d", values[0]);
		for (int i = 1; i < row; i++) {
			printf("%d", values[i]);

		for (int j = 1; j <= row; j++) {
			values[j] += values[j - 1];
			printf("%d", values[j]);
		}
		
			

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
