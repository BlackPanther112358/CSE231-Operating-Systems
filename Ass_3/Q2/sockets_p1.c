#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define array_size 50
#define string_length 10

char string_array[array_size][string_length + 1];

void generate_string_array(){
    for(int i = 0; i < array_size; i++){
        for(int j = 0; j < string_length; j++){
            string_array[i][j] = (rand() % 26) + 97;
        }
        string_array[i][string_length] = '\0';
    }
}

int main(){

    generate_string_array();

    // for(int i = 0; i < array_size; i++){
    //     printf("%s\n", string_array[i]);
    // }

    

}
