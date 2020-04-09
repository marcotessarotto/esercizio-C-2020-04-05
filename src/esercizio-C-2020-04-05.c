#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct{
   char * char_array;
   int length_char_array;
}line;

void print_line(line lines);

int main(int argc, char *argv[]) {

	if(TRUE){
		printf("TEST\n");
	}

	int number_of_lines = 1;
	line * lines = calloc(number_of_lines, sizeof(line));

	char ch;
	ch = getchar();
	int counts_chars_on_one_line = 1;


	while(ch != EOF){
		if(ch == '\n'){
			counts_chars_on_one_line = 0;
			number_of_lines++;
			lines = realloc(lines, number_of_lines * sizeof(line));
			if (lines == NULL) {
				perror("realloc error!");
				exit(EXIT_FAILURE);
			}
			//compare_rows(lines, number_of_lines);
		}else{
			lines[number_of_lines -1].char_array = realloc(lines[number_of_lines -1].char_array, counts_chars_on_one_line * sizeof(char));
			lines[number_of_lines -1].char_array[counts_chars_on_one_line -1] = ch;
			lines[number_of_lines -1].length_char_array = counts_chars_on_one_line;

			if (lines[number_of_lines -1].char_array == NULL) {
				perror("realloc error!");
				exit(EXIT_FAILURE);
			}
		}
		ch = getchar();
		counts_chars_on_one_line++;
	}

	for(int i=0 ; i<number_of_lines ; i++){
		print_line(lines[i]);
	}

	return EXIT_SUCCESS;
}

void print_line(line lines){
	if(lines.char_array != NULL){
		printf("[");
		for( int i=0 ; i<lines.length_char_array ; i++){
			printf("%c ", lines.char_array[i]);
		}
		printf("]\n");
	}
}
/*
void compare_rows(line lines, int number_of_lines){
	lines[number_of_lines -2].char_array
}

int compare_array(char *char_array1, int length_char_array1 ,char *char_array2, int length_char_array2){
	if(length_char_array1)
}
*/
