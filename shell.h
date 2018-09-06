#define PATH_MA 10008


void *prompt(char* username, char hostname[], char path[]);
void print_name();
void *get_path(char curent_path[],char path[],char print_path[]);
int is_builtin(char** argv);
char** parse(char* input,char* delem);
int ls_process(char** argv);
int execute_comm(char** argv);
void sigh();
void pinfo(char** argp);
void remind(char** argp);

char hostname[256];
char path[PATH_MA];
char curent_path[PATH_MA];
char username[PATH_MA];
char print_path[PATH_MA];
int bcg_number;

char* command;
