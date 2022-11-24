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
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define array_size 50
#define string_length 10
#define block_size 5

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



    return 0;

}
