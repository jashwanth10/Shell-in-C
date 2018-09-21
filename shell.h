#define PATH_MA 10008


void *prompt(char* username, char hostname[], char path[]);
void print_name();
void *get_path(char curent_path[],char path[],char print_path[]);
int is_builtin(char** argv);
char** parse(char* input,char* delem);
int ls_process(char** argv);
int execute_comm(char** argv,char* arg);
void sigh();
void pinfo(char** argp);
void remind(char** argp);
char** passing(char** argp);
int piping(char* arg);
void sigchandler();
void sigzhandler();
int fore_pid;
char fore_name[126];
int main_pid;
typedef struct node{
    char process_name[256];
    int pid;
    int state;
}node;

node process[256];
int process_ct;


char hostname[256];
char path[PATH_MA];
char curent_path[PATH_MA];
char username[PATH_MA];
char print_path[PATH_MA];
int bcg_number;

char* command;
