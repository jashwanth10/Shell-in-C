#include "shell.h"
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

void pinfo(char** argp){

    int cur_proc_flag = 0;

    //printf("i = %d,argp = %s",i,argp[2]);


    if(argp[0] != NULL){
        argp[0] = strtok(argp[0],"\n");
    }
    char argi[50];
    if(argp[1] == NULL){
        int z = 0;
        cur_proc_flag = 1;
        pid_t pi = getpid();
        int arr[50];

        int len = 0;
        while(pi>0){
            arr[len++] = pi% 10;
            pi /= 10;
        }
        int ii = 0;
        while(ii<len){
            argi[ii] = arr[len - ii - 1]  + '0';
            ii++;
        }
        argi[ii] = '\0';
        argp[1] = argi;
        argp[2] = NULL;
        //printf("%s\n",argp[1]);
    }else{
        argp[1] = strtok(argp[1],"\n");
        argp[2] = NULL;
    }
    char file[10000];
    char* to = file;
    char strt[100] = "/proc/";
//    printf("%s\n",argp[1]);
    strcat(strt,argp[1]);
    strcat(strt,"/status");
//    printf("%s\n",strt);

    int i = 0;

    if(i > 2){
        printf("Error: Enter Only one pid\n");
        return;
    }
    char* pid;
    if(cur_proc_flag == 1){
        pid_t pd = getpid();
    }else{
        pid = argi;
    }
    int fd;


    if((fd = open(strt,O_RDONLY)) == -1){
        perror("Error: ");
        return;
    }
    else{
        int pointer = 0;
        while(read(fd,to,1) != 0){
            to++;
        }
        char* tok = strtok(file,"\n: ");
        int i = 0;
        int active = 0;
        int activ_2 = 0;
        char* status_ans= NULL;
        char* vm_ans = NULL;
        while(tok != NULL){

        //    printf("i = %d, %s\n",i,tok);
            if(active == 1){
                status_ans = tok;
                active = 0;
            }
            if(activ_2 == 2){
                vm_ans = tok;
                activ_2 = 0;
            }
            if(activ_2 == 1){
                activ_2 ++;
            }
            if(strcmp(tok,"State") == 0){
                active = 1;
            }
            if(strcmp(tok,"VmSize") == 0){
                activ_2 = 1;
            }

            tok = strtok(NULL,"\n: ");
            i++;
        }
        char buf[10000];

        char end[100] = "/proc/";
        //printf("%s\n",argp[1]);
        strcat(end,argp[1]);
        strcat(end,"/exe");
        //printf("%s\n",strt);

        int r = readlink(end,buf,sizeof(buf));

        if(cur_proc_flag == 1){
            printf("Pid -- %d\n",getpid());
        }else{
            printf("Pid -- %s\n",argp[1]);
        }

        printf("Process Status -- %s\n",status_ans);
        printf("%s{Virtual-Memory}\n",vm_ans);
        if(r != -1){
            printf("Executable Path -- %s\n",buf);
        }else{
            printf("Executable Path -- (No Permission)\n");
        }
    }








}
