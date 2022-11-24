#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#define array_size 50
#define string_length 10
#define block_size 5
#define socket_path "socket"

char string_array[array_size][string_length + 1];
struct sockaddr_un local;
struct timespec begin, end;

void generate_string_array(){
    for(int i = 0; i < array_size; i++){
        for(int j = 0; j < string_length; j++){
            string_array[i][j] = (rand() % 26) + 97;
        }
        string_array[i][string_length] = '\0';
    }
}

void print_string_array(){
    for(int i = 0; i < array_size; i++){
        printf("%s\n", string_array[i]);
    }
}

int main(){

    srand(time(NULL));

    generate_string_array();
    // print_string_array();

    int socket_id = socket(AF_UNIX, SOCK_STREAM, 0);
    if(socket_id == -1) {perror("Socket error"); exit(1);}

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, socket_path);
    printf("Trying to connect...\n");
    if(connect(socket_id, (struct sockaddr *)&local, strlen(local.sun_path) + sizeof(local.sun_family)) == -1) {perror("Connect error"); exit(1);}
    printf("Connected.\n");

    int index = 0, res;

    clock_gettime(CLOCK_REALTIME, &begin);

    while(index < array_size){

        for(int i = 0; i < block_size; i++){
            if(index + i >= array_size) break;
            char s[string_length + 4] = {0};
            if((index + i)< 9){
                char num[1];
                sprintf(num, "%d", index + i + 1);
                strcat(s, "0");
                strcat(s, num);
                strcat(s, " ");
                strcat(s, string_array[index + i]);
            }else{
                char num[2];
                sprintf(num, "%d", index + i + 1);
                strcat(s, num);
                strcat(s, " ");
                strcat(s, string_array[index + i]);
            }
            res = write(socket_id, s, string_length + 4);
            if(res == -1) {perror("Write error"); exit(1);}
            if(res != (string_length + 4)) printf("Write error: %d bytes written.\n", res);
            printf("Sent: %s\n", s);
        }

        res = read(socket_id, (&index), sizeof(int));
        if(res == -1) {perror("Read error"); exit(1);}
        if(res != sizeof(int)) printf("Read error: %d bytes read.\n", res);
        printf("Received: %d\n", index);

    } 

    clock_gettime(CLOCK_REALTIME, &end);
    float runtime = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;

    close(socket_id);

    printf("Runtime: %f\n", runtime);

    return 0;

}
