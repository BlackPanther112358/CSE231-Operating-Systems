#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define STR_LEN 100
bool use_threads = false;
char* username;
char cwd[PATH_MAX];

void init(){
    getcwd(cwd, sizeof(cwd));
    username = getlogin();
}

void cd(int argc, char* argv[]){
    if(argc > 3){
        printf("Too many arguements\n");
        return;
    }

    bool flag_p = false, flag_l = false;
    int i = 1;

    for(i; i < argc; i++){
        if(argv[i][0] == '-'){
            char* itr = (char*)(&argv[i][1]);
            while(*itr){
                if(*itr == 'P') flag_p = true;
                else if(*itr == 'L') flag_l = true;
                else{
                    printf("Invalid option passed\n");
                    return;
                }
                itr++;
            }
        }else break;
    }

    char* path;
    if(i == argc) path = getenv("HOME");
    else if(i < (argc - 1)){
        printf("Too many arguments passed\n");
        return;
    }else path = argv[i];

    if(flag_p){
        char actual_path[PATH_MAX];
        char* ret = realpath(path, actual_path);
        if(ret == NULL){
            printf("Path not found\n");
            return;
        }else path = actual_path;
    }

    int ret_val = chdir(path);
    if(ret_val == 0){
        getcwd(cwd, sizeof(cwd));
    }else{
        printf("%s: No such file or directory\n", path);
    }
    return;
}

void echo(int argc, char* argv[]){

    bool flag_n = false, flag_e = false;
    int i = 1;

    for(i; i < argc; i++){
        if(argv[i][0] == '-'){
            char* itr = (char*)(&argv[i][1]);
            while(*itr){
                if(*itr == 'n') flag_n = true;
                else if(*itr == 'e') flag_e = true;
                else{
                    printf("Invalid option passed\n");
                    return;
                }
                itr++;
            }
        }else break;
    }

    for(i; i < argc; i++){
        if((argv[i][0] == '"') && (argv[i][strlen(argv[i]) - 1] == '"')){
            for(int j = 1; j < strlen(argv[i]) - 1; j++){
                if(argv[i][j] == '\\'){
                    if(!flag_e){
                        printf("%c", argv[i][j]);
                        continue;
                    }
                    i++;
                    if(argv[i][j] == 'n') printf("\n");
                    else if(argv[i][j] == 't') printf("\t");
                    else if(argv[i][j] == 'v') printf("\v");
                    else if(argv[i][j] == 'b') printf("\b");
                    else if(argv[i][j] == 'c') break;
                    else if(argv[i][j] == 'e') printf("\e");
                }else{
                    printf("%c", argv[i][j]);
                }
            }
            printf(" ");
        }else{
            for(int j = 0; j < strlen(argv[i]); j++){
                if(argv[i][j] == '\\'){
                    if(!flag_e){
                        printf("%c", argv[i][j]);
                        continue;
                    }
                    j++;
                    if(argv[i][j] == 'n') printf("\n");
                    else if(argv[i][j] == 't') printf("\t");
                    else if(argv[i][j] == 'v') printf("\v");
                    else if(argv[i][j] == 'b') printf("\b");
                    else if(argv[i][j] == 'c') break;
                    else if(argv[i][j] == 'e') printf("\e");
                }else{
                    printf("%c", argv[i][j]);
                }
            }
            printf(" ");
        }
    }
    if(!flag_n) printf("\n");
    return;
}

void pwd(int argc, char* argv[]){
    
    bool flag_p = false, flag_l = false;
    int i = 1;

    for(i; i < argc; i++){
        if(argv[i][0] == '-'){
            char* itr = (char*)(&argv[i][1]);
            while(*itr){
                if(*itr == 'P') flag_p = true;
                else if(*itr == 'L') flag_l = true;
                else{
                    printf("Invalid option passed\n");
                    return;
                }
                itr++;
            }
        }else{
            printf("Invalid argument for pwd command\n");
            return;
        }
    }

    if(flag_l){
        printf("%s\n", getenv("PATH"));
    }else{
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }

    return;
}

void ls(int argc, char* argv[]){
    if(!use_threads){
        pid_t pid = fork();
        if(pid < 0){
            printf("Error occured while forking, try again\n");
            return;
        }else if(pid == 0){
            execvp("/home/aakarsh/OS_Ass/Ass_1/ls", argv);
        }else{
            wait(NULL);
        }
    }else{
        argv[0] = "/home/aakarsh/OS_Ass/Ass_1/ls";
        char args[STR_LEN] = {0};
        for(int i = 0; i < argc; i++){
            strcat(args, argv[i]);
            strcat(args, " ");
        }
        pthread_t ptid;
        pthread_create(&ptid, NULL, (void*)(&system), args);
        pthread_join(ptid, NULL);
    }
    return;
}

void cat(int argc, char* argv[]){
    if(!use_threads){
        pid_t pid = fork();
        if(pid < 0){
            printf("Error occured while forking, try again\n");
            return;
        }else if(pid == 0){
            execvp("/home/aakarsh/OS_Ass/Ass_1/cat", argv);
        }else{
            wait(NULL);
        }
    }else{
        argv[0] = "/home/aakarsh/OS_Ass/Ass_1/cat";
        char args[STR_LEN] = {0};
        for(int i = 0; i < argc; i++){
            strcat(args, argv[i]);
            strcat(args, " ");
        }
        pthread_t ptid;
        pthread_create(&ptid, NULL, (void*)(&system), args);
        pthread_join(ptid, NULL);
    }
    return;
}

void date(int argc, char* argv[]){
    if(!use_threads){
        pid_t pid = fork();
        if(pid < 0){
            printf("Error occured while forking, try again\n");
            return;
        }else if(pid == 0){
            execvp("/home/aakarsh/OS_Ass/Ass_1/date", argv);
        }else{
            wait(NULL);
        }
    }else{
        argv[0] = "/home/aakarsh/OS_Ass/Ass_1/date";
        char args[STR_LEN] = {0};
        for(int i = 0; i < argc; i++){
            strcat(args, argv[i]);
            strcat(args, " ");
        }
        pthread_t ptid;
        pthread_create(&ptid, NULL, (void*)(&system), args);
        pthread_join(ptid, NULL);
    }
    return;
}

void rm(int argc, char* argv[]){
    if(!use_threads){
        pid_t pid = fork();
        if(pid < 0){
            printf("Error occured while forking, try again\n");
            return;
        }else if(pid == 0){
            execvp("/home/aakarsh/OS_Ass/Ass_1/rm", argv);
        }else{
            wait(NULL);
        }
    }else{
        argv[0] = "/home/aakarsh/OS_Ass/Ass_1/rm";
        char args[STR_LEN] = {0};
        for(int i = 0; i < argc; i++){
            strcat(args, argv[i]);
            strcat(args, " ");
        }
        pthread_t ptid;
        pthread_create(&ptid, NULL, (void*)(&system), args);
        pthread_join(ptid, NULL);
    }
    return;
}

void mkdir(int argc, char* argv[]){
    if(!use_threads){
        pid_t pid = fork();
        if(pid < 0){
            printf("Error occured while forking, try again\n");
            return;
        }else if(pid == 0){
            execvp("/home/aakarsh/OS_Ass/Ass_1/mkdir", argv);
        }else{
            wait(NULL);
        }
    }else{
        argv[0] = "/home/aakarsh/OS_Ass/Ass_1/mkdir";
        char args[STR_LEN] = {0};
        for(int i = 0; i < argc; i++){
            strcat(args, argv[i]);
            strcat(args, " ");
        }
        pthread_t ptid;
        pthread_create(&ptid, NULL, (void*)(&system), args);
        pthread_join(ptid, NULL);
    }
    return;
}

bool process(char* inpt){
    char* words[100];
    char delimiter[] = " \n";
    words[0] = strtok(inpt, delimiter);
    int cnt = 1;
    while(words[cnt - 1] != NULL){
        words[cnt] = strtok(NULL, delimiter);
        cnt++;
    }
    words[cnt] = NULL;
    cnt--;
    if(strcmp(words[cnt - 1], "&t") == 0){
        use_threads = true;
        words[cnt - 1] = NULL;
        cnt--;
    }else use_threads = false;
    if(cnt == 0) return false;
    if(strcmp(words[0], "exit") == 0) return true;
    else if(strcmp(words[0], "cd") == 0) cd(cnt, words);
    else if(strcmp(words[0], "pwd") == 0) pwd(cnt, words);
    else if(strcmp(words[0], "echo") == 0) echo(cnt, words);
    else if(strcmp(words[0], "ls") == 0) ls(cnt, words);
    else if(strcmp(words[0], "cat") == 0) cat(cnt, words);
    else if(strcmp(words[0], "date") == 0) date(cnt, words);
    else if(strcmp(words[0], "rm") == 0) rm(cnt, words);
    else if(strcmp(words[0], "mkdir") == 0) mkdir(cnt, words);
    else printf("Command %s not found\n", words[0]);
    return false;
}

int main(){
    printf("-------WELCOME TO THE SHELL-------\n");
    init();
    while(true){
        long unsigned int inpt_len, inpt_size = STR_LEN;
        char* inpt={0};
        printf("[%s %s]$ ", username, cwd);
        inpt_len = getline(&inpt, &inpt_size, stdin);
        inpt[inpt_len - 1] = '\0';
        bool con = process(inpt);
        if(con) break;
    }
    printf("------EXITING THE SHELL------\n");
    return 0;
}