#include <stdio.h>
#include <string.h>

void
swap (char *string, int i, int j) {
    if (i == j) {
        return;
    }
    char temp = string[j];
    string[j] = string[i];
    string[i] = temp;
}

void
insert(char *string, int i, int j) {
    char temp = string[j];
    for (int k = j; k > i; k--) {
        string[k] = string[k - 1];
    }
    string[i] = temp;
}

void
insert_back(char *string, int i, int j) {
    char temp = string[i];
    for (int k = i; k < j; k++) {
        string[k] = string[k + 1];
    }
    string[j] = temp;
}

void
arrange_alpabethical(char *string) {
    int str_l = strlen(string);
    for (int i = 0; i < str_l; i++) {
        for (int j = i + 1; j < str_l; j++) {
            if (string[j] < string[i]) {
                swap(string, i, j);
            }
        }
    }
}

void
permutate(char *string, int level, int max_i) {
    if (level == max_i) {
    printf("%s\n", string);
    return;
    }
    for (int i = level; i <= max_i; i++) {
        insert(string, level, i);
        permutate(string, level + 1, max_i);
        insert_back(string, level, i);
    }
}

void
generate_permutations(char *string) {
    int str_l = strlen(string);
    arrange_alpabethical(string);
    permutate(string, 0, str_l - 1);
}

int main()
{
    char string[21];
    fgets(string, 21, stdin);
    string[strcspn(string, "\n")] = '\0';
    generate_permutations(string);

    return 0;
}