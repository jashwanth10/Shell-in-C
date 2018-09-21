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
#include<sys/mman.h>


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
void sigchandler(){
    if(fore_pid != -1){
        kill(fore_pid,SIGKILL);
    }
    printf("\nCTRL-C recieved\n");
    return;
}
void sigzhandler(int sig_int){
    pid_t wpid;
	int status;
    if(main_pid != getpid())return;
    if(fore_pid != -1){
        process_ct++;
        strcpy(process[process_ct].process_name,fore_name);
        process[process_ct].pid = fore_pid;
        process[process_ct].state =0;
        
        kill(fore_pid,SIGTSTP);
    }	
   
    return;
}
static int* glob_var;
int execute_comm(char** argv,char* arg)
{
    int ret_val = 1;
    int i = 0;
    int background_proc;
    signal(SIGCHLD,sigh);
    int status;
    int wpid;
    int checkin = 0;
    while(argv[i] != NULL){
        i++;
    }
    i--;
    //argv[i] = strtok(argv[i],"\n");
    if(strcmp(argv[i],"&") == 0){
        background_proc = 1;
        argv[i] = NULL;
    }else{
        background_proc = 0;
    }
    //argv[0] = strtok(argv[0],"\n");
    pid_t pid = fork();
    if(pid == 0){       
        argv = passing(argv);
        setpgid(0,0);
        if(execvp(argv[0],argv) == -1){
            perror("error: ");
            checkin = 1;
            exit(0);
        }

    }else if(pid < 0){
        perror("fork::");
    }
    else if(background_proc == 1){
        sleep(1);
       // if(checkin != 1){
           fore_pid = pid;
            process_ct++;
            process[process_ct].pid = pid;
            int i =0;
            strcpy(process[process_ct].process_name,argv[i]);
            i++;
            while(argv[i] != NULL){
                strcat(strcat(process[process_ct].process_name," "),argv[i]);
                i++;
            }
            process[process_ct].state  = 1;
        //}
        
        return 0;
    }else if(background_proc == 0){
        int status;  
        pid_t wpid;
        fore_pid = pid;
        strcpy(fore_name,argv[0]);
       // wpid = waitpid(pid,&status,0);
        waitpid(fore_pid,NULL,WUNTRACED);   
        fore_pid = -1;
        return 0;
    }
}
