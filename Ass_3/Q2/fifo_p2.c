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

#define array_size 50           // Total number of strings
#define string_length 10        // Length of each string
#define block_size 5            // Number of strings to be sent at a time
#define fifo_path "fifo.txt"    // Path of the fifo file

char string_array[array_size][string_length + 1];

void print_string_array(){
    for(int i = 0; i < array_size; i++){
        printf("%s\n", string_array[i]);
    }
}

int main(){

    // print_string_array();

    int index = 0;
    mkfifo(fifo_path, 0666);

    sleep(5);

    while(index < array_size){

        int fd = open(fifo_path, O_RDONLY);
        int res;
        char s[string_length + 4] = {0};
        while((res = read(fd, (void *)(&s), string_length + 4)) > 0){
            for(int i = 3; i < string_length + 4; i++) string_array[index][i - 3] = s[i];
            printf("Received: %s\n", s);
            index++;
        }
        close(fd);

        fd = open(fifo_path, O_WRONLY);
        write(fd, (void *)(&index), sizeof(int));
        printf("Sent: %d\n", index);
        close(fd);

    } 

    return 0;

}
