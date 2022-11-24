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

#define array_size 50                           // Total number of strings
#define string_length 10                        // Length of each string
#define block_size 5                            // Number of strings to be sent at a time
#define fifo_path_sender "fifo1"            // Path of the writer fifo file
#define fifo_path_receiver "fifo2"          // Path of the reader fifo file

char string_array[array_size][string_length + 1];
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

    int index = 0;

    clock_gettime(CLOCK_REALTIME, &begin);

    while(index < array_size){

        int fd_send = open(fifo_path_sender, O_WRONLY);
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
            write(fd_send, s, string_length + 4);
            printf("Sent: %s\n", s);
        }
        close(fd_send);

        int fd_rcv = open(fifo_path_receiver, O_RDONLY);
        read(fd_rcv, (void *)(&index), sizeof(int));
        printf("Received: %d\n", index);
        close(fd_rcv);

    } 

    clock_gettime(CLOCK_REALTIME, &end);
    float runtime = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;

    printf("Runtime: %f\n", runtime);

    return 0;

}
