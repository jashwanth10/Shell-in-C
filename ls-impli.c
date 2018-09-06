#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include "shell.h"
#include<errno.h>

void print_perms(mode_t st) {
    char perms[11];
    if(S_ISREG(st)) perms[0]='-';
    else if(S_ISDIR(st)) perms[0]='d';
    else if(S_ISFIFO(st)) perms[0]='|';
    else if(S_ISSOCK(st)) perms[0]='s';
    else if(S_ISCHR(st)) perms[0]='c';
    else if(S_ISBLK(st)) perms[0]='b';
    else perms[0]='l';  // S_ISLNK
    perms[1] = (st & S_IRUSR) ? 'r':'-';
    perms[2] = (st & S_IWUSR) ? 'w':'-';
    perms[3] = (st & S_IXUSR) ? 'x':'-';
    perms[4] = (st & S_IRGRP) ? 'r':'-';
    perms[5] = (st & S_IWGRP) ? 'w':'-';
    perms[6] = (st & S_IXGRP) ? 'x':'-';
    perms[7] = (st & S_IROTH) ? 'r':'-';
    perms[8] = (st & S_IWOTH) ? 'w':'-';
    perms[9] = (st & S_IXOTH) ? 'x':'-';
    perms[10] = '\0';
    printf("%s", perms);
}

int ls_process(char** argv)
{
    if(strcmp(argv[0],"ls\n") != 0 && strcmp(argv[0],"ls")!=0){
        return 0;
    }
    char** argls = argv;
    int list_flag = 0,error_flag=0;
    int all_flag = 0;
    int flag = 0;
    int i = 0,j = 0;
    char **direcs = malloc(50 * sizeof(char*));
    while(argls[i] != NULL){

        i++;
    }
    argls[i-1] = strtok(argls[i-1],"\n");
    i=  0;
    while(argls[i] != NULL){

        if(argls[i][0] == '-'){
            if(strcmp(argls[i],"-la") == 0 || strcmp(argls[i],"-al") == 0){
                list_flag = 1;
                all_flag = 1;
            }

            else if(strcmp(argls[i],"-l") == 0){
                list_flag = 1;
            }
            else if(strcmp(argls[i],"-a") == 0){
                all_flag = 1;
            }
            else{
                error_flag = 1;
            }
        }
        else{
            if(strcmp(argls[i],"ls") != 0){
                direcs[j] = argls[i];
                j++;
            }
            if(strcmp(argls[i],"ls") == 0 && i != 0){
                direcs[j] = argls[i];
                j++;
            }

        }
        i++;
    }
    direcs[j] = NULL;
    if(j == 0){
        direcs[j] = ".";
        direcs[j+1] = NULL;
    }
    i = 0;
    if(error_flag == 0)

    while(direcs[i] != NULL){
        int total = 0;
        DIR *mydir;
        struct dirent *myfile;
        struct stat mystat;
        char restore[PATH_MA];
        if(getcwd(restore, PATH_MA) == NULL){
            restore[0] = '-';
            restore[1] = '\0';
        }
        char* test = restore;
        strcat(strcat(test,"/"),direcs[i]);
        chdir(test);
        mydir = opendir(test);
        if(mydir != NULL){
            printf("%s:\n",direcs[i]);
            char buf[128];
            struct passwd pwent, * pwentp;
            struct group grp, * grpt;
            char datestring[256];
            struct tm time;
            while((myfile = readdir(mydir)) != NULL)
            {
                if(list_flag == 1 ){
                    stat(myfile->d_name, &mystat);
                    if(all_flag == 0){
                        if(myfile->d_name[0] == '.'){
                            continue;
                        }
                    }
                    print_perms(mystat.st_mode);
                    total += mystat.st_blocks;
                    printf(" %d", (int)mystat.st_nlink);
                    if (!getpwuid_r(mystat.st_uid, &pwent, buf, sizeof(buf), &pwentp))
                    printf(" %s", pwent.pw_name);
                    else
                    printf(" %d", mystat.st_uid);

                    if (!getgrgid_r (mystat.st_gid, &grp, buf, sizeof(buf), &grpt))
                    printf(" %s", grp.gr_name);
                    else
                    printf(" %d", mystat.st_gid);
                    printf(" %5d", (int)mystat.st_size);

                    localtime_r(&mystat.st_mtime, &time);
                    /* Get localized date string. */
                    strftime(datestring, sizeof(datestring), "%F %T", &time);

                    printf(" %s %s\n", datestring, myfile->d_name);

                }else{
                    if(all_flag == 1){
                        printf("%s ", myfile->d_name);
                    }else{
                        if(strcmp(myfile->d_name,".") != 0 && strcmp(myfile->d_name, "..") !=0 ){
                            printf("%s ", myfile->d_name);
                        }
                    }
                }

            }
        if(list_flag == 1)    printf("total = %d\n",total/2);

        }else{
            perror(direcs[i]);
        }

        chdir(curent_path);
        printf("\n");

        closedir(mydir);
        i++;
    }
    else{
        printf("flag error: incorrect flags\n");
    }
    return 1;
}
