#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void memorize_array(char ** tot, char * array, int length, int counter) {
    memcpy(&(tot[counter-1]), array, length * sizeof(char));
}

void control_reps(char ** tot, int length, int counter) {
    int start = counter-1;
    for(int i=counter-2; i >= 0; i--){
        int check = memcmp(&(tot[start]), &(tot[i]), length * sizeof(char));
        if (check == 0){
            int rep = start - i;
            printf("\n***questa riga è stata già letta %d righe fa***\n", rep);
        }
    }
}

int main (int argc, char * argv []) {
    char input;
    int i = 0;
    int counter = 0;
    unsigned int length = 1;
    char * array_char = calloc(length, sizeof(char));
    char ** tot_array = calloc(length, sizeof(char *));
    while((input = getchar()) != EOF){
        if(input != '\n'){
            array_char[i] = input;
            length++;
            array_char = realloc(array_char, length * sizeof(char));
            i++;
        }
        else {
            counter++;
            tot_array = realloc(tot_array, counter * sizeof(char *));
            memorize_array(tot_array, array_char, length, counter);
            control_reps(tot_array, length, counter);
            length = 0;
            i = 0;
        }
    }
    
    free (array_char);
    free (tot_array);
    
    return 0;
}
