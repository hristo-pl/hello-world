/*
Read an email address from the input and parse the name and the domain from it and greet the user and welcome to the company.
For example if the provided input as sara@alphabet.com, Your output should be Hi Sara, Welcome to Alphabet. Output should have first letter of user name and company name as a capital letter.

Note: Domain extentention may not be .com always.
Example input:

sara@alphabet.com

Example output:

Hi Sara, Welcome to Alphabet
*/
#include<stdio.h>
#include "parce_email_functions.h"

int main() {
    char email[100] = "\0";
    char name[50] = "\0";
    char company[50] = "\0";
    fgets(email, 100, stdin);
    
    parce_email(email, name, company);

    printf("Hi %s, Welcome to %s", name, company);
    
    return 0;
}