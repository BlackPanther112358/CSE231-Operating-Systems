#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){

    bool flag_u = false, flag_I = false;

    time_t t = time(NULL);
    struct tm T = *localtime(&t);

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            char* itr = (char*)(&argv[i][1]);
            while(*itr){
                if(*itr == 'u') flag_u = true;
                else if(*itr == 'I') flag_I = true;
                else{
                    printf("Invalid option passed\n");
                    exit(EXIT_FAILURE);
                }
                itr++;
            }
        }
    }

    if(flag_I){
        printf("%04d-%02d-%02d\n", T.tm_year + 1900, T.tm_mon + 1, T.tm_mday);
    }else if(flag_u){
        struct tm *GMT = gmtime(&t);
        time_t utctime = mktime(GMT);
        printf(ctime(&utctime));
    }else{
        printf(ctime(&t)); 
    }

    return 0;
}