#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "shell.h"
#include<fcntl.h>
#include<unistd.h>
#include<error.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>

void UpdateBg(){
    pid_t wpid;
    int status;    
    for(int i =1;i<=process_ct;i++){
        wpid = waitpid(process[i].pid,&status,WUNTRACED|WNOHANG);
        if(wpid > 0){    
            if(WIFSTOPPED(status)){
                process[i].state = 0;
            }else if(WIFCONTINUED(status)){
                process[i].state = 1;
            }
        }
        else if(wpid < 0){
            for(int j = i;j<process_ct;j++){
                    process[j] = process[j+1];
                }
            process_ct--;
        }
    }
    return;
}

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
        else{
            if(chdir(path) != 0){
                perror("cannot change directory");
            }
            return 1;
        }
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
        return 1;
    }
    else if(strcmp(argv[0],"setenv") == 0){
        int i = 1,ct = 0;    
        while(argv[i] != NULL){
            i++;ct++;
        }
        if(ct==0 || ct > 2){
            printf("Error:Two Arguments are required\n");
            return 1;
        }else{
            if(setenv(argv[1],argv[2],1) == -1){
                perror("Error ");
            }
            return 1;
        }
    }else if(strcmp(argv[0],"unsetenv") == 0){
         int i = 1,ct = 0;    
        while(argv[i] != NULL){
            i++;ct++;
        }
         if(ct==0 || ct > 1){
            printf("Error:One Arguments are required\n");
            return 1;
        }else{
            if(unsetenv(argv[1]) == -1){
                perror("Error ");
            }
            return 1;
        }
    }else if(strcmp(argv[0],"jobs") == 0){
        int i = 0;
        UpdateBg();
        UpdateBg();
        for(int i=1;i<=process_ct;i++){
            int status;
            if(process[i].state == 1)printf("[%d] Running %s[%d]\n",i,process[i].process_name,process[i].pid);
            else if(process[i].state == 0)printf("[%d] Stopped %s[%d]\n",i,process[i].process_name,process[i].pid);   
        }
        return 1;
    }
    else if(strcmp(argv[0],"kjob") == 0){
        UpdateBg();
        int i = 1;
        while(argv[i] != NULL){
            i++;
        }
        if(i != 3){
            printf("Usage: kjob [JobNumber] [Signal]\n");
            return 1;
        }else{
            int j_no = atoi(argv[1]);
            int s_no = atoi(argv[2]);
            if(!(j_no <= process_ct && j_no >= 1)){
                printf("Mentioned Job Doesn't Exist\n");
                return 1;
            }else{
                if(kill(process[j_no].pid,s_no) == -1){
                    perror("Error:");
                }
                return 1;
            }
        }
    }
    else if(strcmp(argv[0],"fg") == 0){
        UpdateBg();
        int i =0 ;
        while(argv[i] != NULL){
            i++;
        }
        if(i > 2){
            printf("Usage : fg [JobNumber]\n");
            return 1;
        }
        int j_no;
        if(i == 1){
            j_no = process_ct;
        }
        else j_no = atoi(argv[1]);
        int status;
        fore_pid = process[j_no].pid;
        printf("%s with pid [%d] foreground\n",process[j_no].process_name,fore_pid);
        pid_t pid = waitpid(process[j_no].pid,&status,0);
        

        
        return 1;
    }
    else if(strcmp(argv[0],"bg") == 0){
        UpdateBg();
         int i =0 ;
        while(argv[i] != NULL){
            i++;
        }
        if(i > 2){
            printf("Usage : fg [JobNumber]\n");
            return 1;
        }
        int j_no;
        if(i == 1){
            j_no = process_ct;
            
        }
        else j_no = atoi(argv[1]);
        process[j_no].state = 1;
        fore_pid = process[j_no].pid;
        if(kill(process[j_no].pid,SIGCONT) == -1){
            process[j_no].state = 0;
            perror("Error: ");

        }
        return 1;
    }else if(strcmp(argv[0],"overkill") == 0){
        int i =0;
        while(argv[i] != NULL){
            i++;
        }    
        if(i!=1){
            printf("No Arguments required\n");
            return 1;
        }
        for(int i = 1;i<=process_ct;i++){
            if(kill(process[i].pid,SIGKILL) == -1){
                perror("Error: ");
            }
            UpdateBg();
        }
        return 1;
    }else if(strcmp(argv[0],"exit") == 0){
        if(kill(getpid(),SIGKILL) == -1){
            perror("Error");
            return 1;
        }
    }
    return 0;
}
