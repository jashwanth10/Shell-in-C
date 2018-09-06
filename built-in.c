#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "shell.h"
#include<fcntl.h>
#include<unistd.h>
#include<error.h>

int is_builtin(char** argv){
    if(strcmp(argv[0],"cd") == 0){
        if(argv[1] != NULL){
            argv[1] = strtok(argv[1],"\n ");
            if(strcmp(argv[1],"~") == 0){
                argv[1] = path;
            }
            if(chdir(argv[1]) != 0){
                perror("cannot change directory");
            }
            return 1;
        }
    }else if(strcmp(argv[0],"cd\n") == 0){
        if(chdir(path) != 0){
            perror("cannot change directory");
        }
        return 1;
    }
    else if(strcmp(argv[0],"echo") == 0){

        int i = 1;
        while(argv[i] != NULL){
            i++;
        }
        argv[i-1] = strtok(argv[i-1],"\n");
        i = 1;
        while(argv[i] != NULL){
            printf("%s ",argv[i]);
            i++;
        }
        return 1;
    }
    else if(strcmp(argv[0],"pwd\n") == 0){
        printf("%s\n",curent_path);
    }
    return 0;
}
