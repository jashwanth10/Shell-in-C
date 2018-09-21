#include "shell.h"
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<string.h>

int f1,f2,f3;

char** passing(char** argv){
    int i =0;
    char* input;
    char* output;    
    while(argv[i] != NULL){
        if(strcmp(argv[i],"<") == 0){
            f1 = 1;
            strcpy(argv[i]," ");
            argv[i] = NULL;
            input = argv[i+1];
        }else if(strcmp(argv[i],">") == 0){
            f2 = 1;
            strcpy(argv[i]," ");
            argv[i] = NULL;
            argv[i+1] = strtok(argv[i+1],"\n");
            output = argv[i+1];
        }else if(strcmp(argv[i],">>")==0){
            f3 = 1;
            strcpy(argv[i]," ");
            argv[i] = NULL;
            output = argv[i+1];
        }
        i++;
    }
    int fd1,fd2,fd3;
    int r1,r2,r3;
        r1 = dup(0);
        r2 = dup(1);
        if(f1 == 1){
            fd1 = open(input,O_RDONLY,0);
            if(fd1<0){
                perror("opening file:");
                //exit(1);
            }
            dup2(fd1,0);
            close(fd1);
        }if(f2 == 1){
//            printf("hudscd");
            fd2 = open(output,O_WRONLY|O_CREAT|O_TRUNC,0644);
            if(fd2 < 0){
                fd2 = creat(output,0644);
            }
            if(fd2 < 0){
                perror("creating file:");
               // exit(1);
            }
            dup2(fd2,1);
            close(fd2);
        }if(f3 == 1){
            fd3 = open(output,O_RDWR|O_APPEND,0);
            if(fd3 < 0){
                perror("appending file:");
             //   exit(1);
            }
            dup2(fd3,1);
            close(fd3);
        }
        if(f1 == 1){
            dup2(fd1,r1);
        }if(f2 == 1){
            dup2(fd2,r2);
        }if(f3 == 1){
            dup2(fd3,r2);
        }
    
    return argv;
}
