#include "shell.h"
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
#include<time.h>


void sigh(){
    pid_t wpid;
	int status;
	wpid=waitpid(-1,&status,WNOHANG);
    //if(wpid < 0){
    //    perror("wid:");
    //}
	if(wpid>0	&& (WIFEXITED(status)==1)){
			printf("\nProcess with pid %d exited normally\n",wpid);

            bcg_number  -= 1;
	}
	if(wpid >0 && (WIFSIGNALED(status)==1)){
			printf("\nProcess with pid %d exited due to a user-defined signal\n",wpid);
            bcg_number -= 1;
	}

    return;
}

int execute_comm(char** argv)
{
    int ret_val = 1;
    int i = 0;
    int background_proc;
    signal(SIGCHLD,sigh);
    int status;
    int wpid;
    while(argv[i] != NULL){
        i++;
    }
    i--;
    argv[i] = strtok(argv[i],"\n");
    if(strcmp(argv[i],"&") == 0){
        background_proc = 1;
        argv[i] = NULL;
    }else{
        background_proc = 0;
    }
    argv[0] = strtok(argv[0],"\n");
    pid_t pid = fork();
    if(pid == 0){
        bcg_number += 1;
        printf("[%d] %d\n",bcg_number,getpid());
        if(execvp(argv[0],argv) == -1){
            perror("error: ");
            exit(0);
        }

    }else if(pid < 0){
        perror("fork::");
    }
    else if(background_proc == 1){
        sleep(1);
        return 0;
    }else if(background_proc == 0){
        wait(NULL);
        return 0;
    }
}
