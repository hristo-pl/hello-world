#include "parce_email_functions.h"
#include <string.h>

void parce_email(char *email, char *name, char *company) {
    int company_start = 0;
    
    //printf("Name:\n");
    for (int i = 0; i < strlen(email); i++) {
        
        if (email[i] ==  '@') {
            company_start = i + 1;
            break;
        }
        
        
        name[i] = email[i];
        //printf("%c-", name[i]);
    }
    //printf("\n");
    
    //printf("Company:\n");
    for (int i = company_start; i < strlen(email); i++) {
        
        if (email[i] ==  '.') {
            break;
        }
        
        company[i - company_start] = email[i];
        //printf("%c-", company[i - company_start]);
    }
    //printf("\n");
    
}