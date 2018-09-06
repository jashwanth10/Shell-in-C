#include "shell.h"
#include<readline/readline.h>
#include<string.h>

int main(){
    bcg_number = 0;
    char* input = NULL;
    size_t m = 0;
    char* handle = NULL;
    char** argg;
    handle = prompt(username,hostname,path);
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
                char** argp = parse(argg[i]," ");
                int j = 0;
                while(argp[j] != NULL){
                    j++;
                }

                if(!is_builtin(argp)){
                    if(strcmp(argp[0],"ls") == 0||strcmp(argp[0],"ls\n") == 0){
                        ls_process(argp);
                    }else if(strcmp(argp[0],"pinfo") ==0 || strcmp(argp[0],"pinfo\n") ==0 ){
                            printf("argp = %s",argp[0]);
                        pinfo(argp);
                    }else if(strcmp(argp[0],"remindme") == 0||strcmp(argp[0],"remindme\n") == 0){
                        remind(argp);
                    }
                    else{

                        execute_comm(argp);
                    }
                }
                i++;
            }
        }

    }


    return 0;
}
