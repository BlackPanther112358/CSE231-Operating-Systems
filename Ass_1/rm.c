#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

char cwd[PATH_MAX];
bool flag_f = false;
bool flag_v = false;

void _rm(char *file){
    struct stat path_check;
    stat(file, &path_check);
    if(S_ISDIR(path_check.st_mode)){
        printf("%s is a directory not a file\n", file);
        exit(EXIT_FAILURE);
    }
    int ret_val = remove(file);
    if((ret_val != 0) && (!flag_f)){
        printf("No such file or directory\n");
        exit(EXIT_FAILURE);
    }
    if(flag_v) printf("removed %s\n", file);
    return;
}

int main(int argc, char *argv[]){

    getcwd(cwd, sizeof(cwd));

    if(argc == 1){
        printf("Too few arguements passed\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            char* itr = (char*)(&argv[i][1]);
            while(*itr){
                if(*itr == 'f') flag_f = true;
                else if(*itr == 'v') flag_v = true;
                else{
                    printf("Invalid option passed\n");
                    exit(EXIT_FAILURE);
                }
                itr++;
            }
        }
    }

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-') continue;
        _rm(argv[i]);
    }

	return 0;
}