#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

bool flag_n = false;
bool flag_E = false;

void _cat(const char *file){
	struct stat path_check;
    stat(file, &path_check);
    if(S_ISDIR(path_check.st_mode)){
        printf("%s is a directory not a file\n", file);
        exit(EXIT_FAILURE);
    }
    FILE* file_handle = fopen(file, "r");
    if(file_handle == NULL){
        printf("File not found\n");
        exit(EXIT_FAILURE);
    }
    printf("%s: \n", file);
    int line_cnt = 1;
    size_t line_length = 0, length;
    char* file_line;
    while((length = getline(&file_line, &line_length, file_handle)) != -1){
        file_line[length - 1] = '\0';
        if(flag_n) printf("%d ", line_cnt);
        printf("%s ", file_line);
        if(flag_E) printf("$\n");
        else printf("\n");
        line_cnt++;
    }
    return;
}


int main(int argc, const char *argv[]){

    if(argc == 1){
        printf("Too few arguements passed\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            char* itr = (char*)(&argv[i][1]);
            while(*itr){
                if(*itr == 'n') flag_n = true;
                else if(*itr == 'E') flag_E = true;
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
        _cat(argv[i]);
    }

	return 0;
}