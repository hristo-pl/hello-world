/*
    Count of characters and digits
    Max Score: 6 | Difficulty: Not Specified

    Read a sentence from the input and print 
    the count of the number of characters and 
    digits present in the given string.
    Example input:

    What do you think about 2020

    Example output:

    19
    4
*/

#include <stdio.h>
#include <string.h>

int count_characters(const char *string) {
    int count = 0;
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int string_len = strlen(string);
    const int alphabet_len = sizeof(alphabet) -1;

    for (int i = 0; i < string_len; i++) {
        for (int j = 0; j < alphabet_len; j++) {
            if (string[i] == alphabet[j]) {
                count++;
                break;
            }
        }
    }

    return count;
}

int count_digits(const char *string) {
    int count = 0;
    const char digits[] = "0123456789";
    const int string_len = strlen(string);
    const int digits_len = sizeof(digits) -1;

    for (int i = 0; i < string_len; i++) {
        for (int j = 0; j < digits_len; j++) {
            if (string[i] == digits[j]) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main() {
    char sentence[100];
    printf("Enter sentence: ");
    fgets(sentence, 100, stdin);
    sentence[strcspn(sentence, "\n")] = '\0';  // Remove newline

    printf("%d\n", count_characters(sentence));
    printf("%d\n", count_digits(sentence));

    return 0;
}