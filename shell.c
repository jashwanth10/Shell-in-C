#include "shell.h"
#include<readline/readline.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(){
    bcg_number = 0;
    char* input = NULL;
    size_t m = 0;
    char* handle = NULL;
    char** argg;
    handle = prompt(username,hostname,path);
    signal(SIGINT,sigchandler);
    signal(SIGTSTP,sigzhandler);
    fore_pid = -1;
    main_pid = getpid();
    while(1){
        print_name(handle);
        if(getline(&input, &m, stdin) != -1){
            //char** args = parse(input,";");
            char* delem = " ;";

            argg = parse(input,";");
            int i=0;
            while(argg[i] != NULL){
                if(strcmp(argg[0],"\n") == 0){
                    i++;
                    continue;

                }
                char* argpass = malloc(100*sizeof(char));
                strcpy(argpass,argg[i]);
                char** argp = parse(argg[i]," \n");

                int j = 0,state = 1;
                while(argp[j] != NULL && state == 1){
                    if(argp[j][0] == '|' || argp[j][strlen(argp[j])-1] == '|'){
                        state = 0;
                        piping(argpass);
                    }
                    j++;
                }
                if(state == 1)
                if(!is_builtin(argp)){
                    if(strcmp(argp[0],"ls") == 0||strcmp(argp[0],"ls\n") == 0){
                        argp = passing(argp); 
                        ls_process(argp);
                    }else if(strcmp(argp[0],"pinfo") ==0 || strcmp(argp[0],"pinfo\n") ==0 ){
                            printf("argp = %s",argp[0]);
                        pinfo(argp);
                    }else if(strcmp(argp[0],"remindme") == 0||strcmp(argp[0],"remindme\n") == 0){
                        remind(argp);
                    }
                    else{     
                        execute_comm(argp,argpass);
                    }
                }
                i++;
                free(argpass);
            }
        }

    }


    return 0;
}
