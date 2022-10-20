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
bool flag_p = false;
bool flag_v = false;

void mk_dir(char* dirs[], int i){
    if(dirs[i] == NULL) return;
    char* cur_path = cwd;
    mkdir(dirs[i], 0777);
    if(flag_v){
        printf("Created directory ");
        for(int j = 0; j <= i; j++){
            printf("%s/", dirs[j]);
        }
        printf("\n");
    }
    chdir(dirs[i]);
    getcwd(cwd, sizeof(cwd));
    mk_dir(dirs, i + 1);
    chdir(cur_path);
    return;
}

void process_dir(char *dir){
	char* dirs[100];
    char delimiter[] = "/";
    dirs[0] = strtok(dir, delimiter);
    int cnt = 1;
    while(dirs[cnt - 1] != NULL){
        dirs[cnt] = strtok(NULL, delimiter);
        cnt++;
    }
    dirs[cnt] = NULL;
    if((cnt > 2) && (!flag_p)){
        printf("Cannot make directory with the given name\n");
        exit(EXIT_FAILURE);
    }
    mk_dir(dirs, 0);
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
                if(*itr == 'p') flag_p = true;
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
        process_dir(argv[i]);
    }

	return 0;
}