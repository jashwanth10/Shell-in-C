#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/wait.h>
#include<signal.h>

int piping(char* argp){
     signal(SIGCHLD,sigh);
    char** argv = parse(argp,"|");
    int fd1[2],fd2[2];
    int ct = 0;
    while(argv[ct]!= NULL){
        //printf("%s ",argv[ct]);
        ct++;
    }
   
    argv[ct-1] = strtok(argv[ct-1],"\n");
    
    for(int i=0;i<ct;i++){
         int check = 0;
        char** argz = parse(argv[i]," ");
        int j = 0;
        while(argz[j] != NULL){
            j++;
        }
        if(strcmp(argz[j - 1],"&") == 0){
            argz[j-1] = NULL;    
            check = 1;
        }
        if(i%2 == 0){
            pipe(fd1);
        }else{
            pipe(fd2);
        }
        pid_t pid = fork();
        if(pid == 0){
            argz = passing(argz);
            if(i==0){
                dup2(fd1[1],1);
            }else if(i == ct-1){
                if(ct%2 == 0){
                    dup2(fd1[0],0);
                }else{
                    dup2(fd2[0],0);
                }
            }
            else{
                if(i%2 == 0){
                    dup2(fd2[0],0);
                    dup2(fd1[1],1);
                }else{
                    dup2(fd1[0],0);
                    dup2(fd2[1],1);
                }
            }
           // printf("%s ",argz[0]);
            if(execvp(argz[0],argz) == -1){
                perror("Error");
                exit(0);
            }
        }else if(pid > 0){
            if(i==0){
                close(fd1[1]);
            }else if(i == ct-1){
                if(i%2 == 0){
                    close(fd1[0]);                    
                }else{
                    close(fd2[0]);                 
                }
            }
            else{
                if(i%2 == 0){
                    close(fd2[0]);
                    close(fd1[1]);
                }else{
                    close(fd1[0]);
                    close(fd2[1]);
                }
            }
            if(check == 0){
                wait(NULL);
            }
        }
        
    }

    return 0;



}
