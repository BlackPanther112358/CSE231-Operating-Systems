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

bool flag_a = false;
bool flag_1 = false;

void _ls(const char *dir){
	struct dirent *d;
	DIR *dh = opendir(dir);
	if (dh == NULL){
		if (errno = ENOENT) printf("Directory not found\n");
		else printf("Unable to read directory\n");
		exit(EXIT_FAILURE);
	}
    printf("%s: \n", dir);
	while ((d = readdir(dh)) != NULL){
		if (!flag_a && d->d_name[0] == '.')
			continue;
		printf("%s  ", d->d_name);
		if(flag_1) printf("\n");
	}
	if(!flag_1) printf("\n");
}


int main(int argc, const char *argv[]){

    bool dir_found = false;

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            char* itr = (char*)(&argv[i][1]);
            while(*itr){
                if(*itr == 'a') flag_a = true;
                else if(*itr == '1') flag_1 = true;
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
        dir_found = true;
        _ls(argv[i]);
    }

    if(!dir_found) _ls(".");

	return 0;
}
