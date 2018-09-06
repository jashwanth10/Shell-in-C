#include "shell.h"
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include<string.h>
#include<time.h>

void remind(char** argp){

    int ti = 0;
    if(argp[1] != NULL){
        int i = 0;
        int y = 1;
        for(int j = 0;j<strlen(argp[1])- 1;j++){
            y *= 10;
        }
        while(argp[1][i] != '\0'){
            if(argp[1][i] <= '9' && argp[1][i] >= '0'){
                ti += (argp[1][i] - '0') * y;
                y /= 10;
            }else{
                printf("Error: give an integer\n");
                return ;
            }
            i++;
        }
        char* message;
        if(argp[2] != NULL){
            message = argp[2];
            long int t = clock();
            pid_t pid = fork();
            if(pid == 0){
                //sleep(ti);
                while(clock()/CLOCKS_PER_SEC < ti);

                printf("\nReminder : %s\n",message);

            }
            if(pid < 0){
                perror("Error: ");
            }else{
                return;
            }
        }else{
            printf("Error: Enter Message\n");
        }

    }else{
        printf("Error: enter time and message\n");
    }
    return;
}
