#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define array_size 5          // Total number of strings
#define string_length 10        // Length of each string
#define block_size 5            // Number of strings to be sent at a time
#define fifo_path_sender "fifo2.txt"            // Path of the writer fifo file
#define fifo_path_receiver "fifo1.txt"          // Path of the reader fifo file

char string_array[array_size][string_length + 1];

void print_string_array(){
    for(int i = 0; i < array_size; i++){
        printf("%s\n", string_array[i]);
    }
}

int main(){

    // print_string_array();

    int index = 0;
    mkfifo(fifo_path_sender, 0666);
    mkfifo(fifo_path_receiver, 0666);

    sleep(5);

    while(index < array_size){

        int fd_rcv = open(fifo_path_receiver, O_RDONLY);
        int fd_send = open(fifo_path_sender, O_WRONLY);
        int res;
        char s[string_length + 4] = {0};
        res = read(fd_rcv, (void *)(&s), string_length + 4);
        if(res == -1) perror("Read error P2");
        while(res > 0){
            printf("Received: %s\n", s);
            // printf("Received: %d\n", res);
            char idx[2];
            idx[0] = s[0];
            idx[1] = s[1];
            idx[2] = '\0';            
            // printf("Received index: %s\n", idx);
            int index = atoi(idx);
            // printf("Received index: %d\n", index);
            for(int i = 3; i < string_length + 4; i++) string_array[index - 1][i - 3] = s[i];
            for(int i = 0; i < string_length + 4; i++) s[i] = '-';
            res = read(fd_rcv, (void *)(&s), string_length + 4);
            if(res == -1) perror("Read error P2");
        }
        // print_string_array();
        write(fd_send, (void *)(&index), sizeof(int));
        printf("Sent: %d\n", index);
        close(fd_rcv);
        close(fd_send);

    } 

    return 0;

}
