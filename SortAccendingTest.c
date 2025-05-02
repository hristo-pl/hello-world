#include<stdio.h>

void sortAccending(int* arrAddress, int size) {
    for (int i = 0; i < size; i++) {
        printf("i_%d: ", i);
        for (int i = 0; i < size; i++) {
            printf("%d, ", *(arrAddress + i));
        }
        printf("\n");

        int temp;
        for (int z = i; z < size; z++) {
            if (*(arrAddress + z) < *(arrAddress + i)) {
                temp = *(arrAddress +z);
                *(arrAddress + z) = *(arrAddress +i);
                *(arrAddress + i) = temp;
            }
        }
    }
    printf("\n");
}

int main() {
    int array[] = {14, 19, 16, 17, 11, 7, 17, 13, 3, 12};
    int arrayLength = sizeof(array)/sizeof(array[0]);

    printf("\n");
    printf("Original array: ");
    for (int i = 0; i < arrayLength; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n");

    printf("Array length: %d\n\n", arrayLength);

    sortAccending(&array[0], arrayLength);
    
    for (int i = 0; i < arrayLength; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n");

    return 0;
}