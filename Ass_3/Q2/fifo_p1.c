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
    mkfifo(fifo_path, 0666);

    sleep(5);

    while(index < array_size){

        int fd = open(fifo_path, O_WRONLY);
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
            write(fd, s, string_length + 4);
            printf("Sent: %s\n", s);
        }
        close(fd);

        fd = open(fifo_path, O_RDONLY);
        read(fd, (void *)(&index), sizeof(int));
        printf("Received: %d\n", index);
        close(fd);

    } 

    return 0;

}
