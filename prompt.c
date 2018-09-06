#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "shell.h"
//#include<sys/types.h>
//#include<sys/wait.h>
#include <sys/utsname.h>
//#include <fcntl.h>
//#include <pwd.h>

#define PATH_MAX 10008

void *get_path(char curent_path[],char path[],char print_path[]){
    if(getcwd(curent_path, PATH_MAX) == NULL){
        curent_path[0] = '-';
        curent_path[1] = '\0';
    }
    if(strlen(curent_path) < strlen(path)){
        return curent_path;
    }
    else{
        for(int i=0;i<strlen(path);i++){
            if(path[i]==curent_path[i]){
                continue;
            }else{
                if(getcwd(print_path, PATH_MAX) == NULL){
                    print_path[0] = '-';
                    print_path[1] = '\0';
                }
                i = strlen(path) + 1;
            }
        }
        print_path[0] = '~';
        for(int j=1;j<=strlen(curent_path)-strlen(path) + 1;j++){
            print_path[j] = curent_path[j - 1 + strlen(path)];
        }
        return print_path;
    }
}

void *prompt(char username[], char hostname[], char path[]){

    int result = getlogin_r(username,256);
    //username = getenv("LOGNAME");
    //printf("%s\n",username);
    if(result != 0){
        username[0] = 'X';
        username[1] = '\0';
    }
    if(gethostname(hostname,PATH_MAX) != 0){
        hostname[0] = 'X';
        hostname[1] = '\0';
    }

    if(getcwd(path, PATH_MAX) == NULL){
        path[0] = '-';
        path[1] = '\0';
    }

    return strcat(strcat(username,"@"),hostname);
}



void print_name(char* handle){
    char username[256];

    char* show = get_path(curent_path, path, print_path);
    printf("<%s:%s>",handle,show);
    return;
}
