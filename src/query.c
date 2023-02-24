#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/query.h"


char* concatene(query *q)
{
    int taille=9+strlen(q->type)+9+1;
    for(int i=0;i<q->nbParams;i++)
    {
        taille+=3;
        taille+=strlen(q->paramsName[i]);
        taille+=2;
        taille+=strlen(q->paramsValue[i]);
    }
    char* res=(char*)malloc(sizeof(char)*taille);
    res=strcpy(res,"\tquerry: ");
    res=strcat(res,q->type);
    res=strcat(res,"\n\tparams:");
    for(int i=0;i<q->nbParams;i++)
    {
        res=strcat(res,"\n\t\t");
        res=strcat(res,q->paramsName[i]);
        res=strcat(res,": ");
        res=strcat(res,q->paramsValue[i]);
    }
    return res;
}
