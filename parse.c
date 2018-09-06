#include "shell.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char** parse(char* input,char* delem){
    int i = 0;
    char** argv = malloc(50 * sizeof(char*));
    char* token = strtok(input,delem);

    while(token != NULL){
        argv[i] = token;
        i++;
        token = strtok(NULL,delem);
    }
    argv[i] = NULL;
    return argv;
}
