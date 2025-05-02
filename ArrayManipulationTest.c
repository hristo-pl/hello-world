#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//fill arr with random numbers by given arr address, range, and arr length.
void fillArrRandNum(int* arrAdress, int min, int max, int length){
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        *(arrAdress + i) = min + rand() % (max - min + 1);
    }
}

// sort int array in accending order.
void sortAccending(int* arrAddress, int size) {
    for (int i = 0; i < size; i++) {
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

// func - take arr and if it have duplicate values, return

//      new arr only with the duplicate values.
// func - take two arr and return the common valkues for both in new arr.

int main() {
    // parameters to generate arr
    int min = 1;
    int max = 20;
    int length = 10;
    int array[length];
    
    fillArrRandNum(&array[0], min, max, sizeof(array)/sizeof(array[0]));
    printf("\nGenerated array: ");
    for (int i = 0; i < length; i++) {
        printf("%d, ", array[i]);
    }
    
    sortAccending(&array[0], length);
    printf("\nSorted array: ");
    for (int i = 0; i < length; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n\n");

    return 0;
}

