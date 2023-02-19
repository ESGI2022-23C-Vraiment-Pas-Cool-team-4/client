#include <string.h>

int login(char* username, char* password){
    if(!strcmp(username, "azerty") && !strcmp(password, "azerty")){
        return 1;
    }else if(!strcmp(username, "admin") && !strcmp(password, "admin")){
        return 2;
    }
    return 0;
}