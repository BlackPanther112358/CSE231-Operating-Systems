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

struct sockaddr_un local, remote;

char string_array[array_size][string_length + 1];

int main(){

    int socket_id = socket(AF_UNIX, SOCK_STREAM, 0);
    if(socket_id == -1) {perror("Socket error"); exit(1);}

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, socket_path);
    unlink(local.sun_path);

    if(bind(socket_id, (struct sockaddr *)&local, strlen(local.sun_path) + sizeof(local.sun_family)) == -1) {perror("Bind error"); exit(1);}

    if(listen(socket_id, 1) == -1) {perror("Listen error"); exit(1);}

    printf("Waiting for a connection...\n");
    int rem_size = sizeof(remote);
    int in_socket_id = accept(socket_id, (struct sockaddr *)&remote, &rem_size);
    if(in_socket_id == -1) {perror("Accept error"); exit(1);}
    printf("Connected.\n");

    int res;
    int index = 0;
    char s[string_length + 4] = {0};

    while(index < array_size){

        for(int i = 0; i < block_size; i++){
            res = read(in_socket_id, (&s), string_length + 4);
            if(res == -1) {perror("Read error"); exit(1);}
            printf("Received: %s\n", s);
            char idx[2];
            idx[0] = s[0];
            idx[1] = s[1];
            idx[2] = '\0';            
            index = atoi(idx);
            for(int i = 3; i < string_length + 4; i++) string_array[index - 1][i - 3] = s[i];
            for(int i = 0; i < string_length + 4; i++) s[i] = '-';
        }

        res = write(in_socket_id, &index, sizeof(int));
        if(res == -1) {perror("Write error"); exit(1);}
        if(res != sizeof(int)) {printf("Write error: %d bytes written.\n", res); exit(1);}
        printf("Sent: %d\n", index);

    }

    close(in_socket_id);

    return 0;

}