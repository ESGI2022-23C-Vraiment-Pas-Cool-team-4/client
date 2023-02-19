#include <string.h>

int login(char* username, char* password){
    if(!strcmp(username, "azerty") && !strcmp(password, "azerty")){
        return 1;
    }
    return 0;
}