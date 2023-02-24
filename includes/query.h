typedef struct{
    char* type;
    char** paramsName;
    char** paramsValue;
    int nbParams;
} query;

char* concatene(query *q);