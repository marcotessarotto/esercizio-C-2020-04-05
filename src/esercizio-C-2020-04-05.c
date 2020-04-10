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


void determines_duplicates(line * lines, int number_of_lines);
int compare_array(char *char_array1, int length_char_array1 ,char *char_array2, int length_char_array2);

int main(int argc, char *argv[]) {

	int number_of_lines = 1;
	line * lines = calloc(number_of_lines, sizeof(line));

	char ch;
	ch = getchar();
	int counts_chars_on_one_line = 1;
	int last_alloc_dimension = -1;


	while(ch != EOF){
		if(ch == '\n'){
			counts_chars_on_one_line = 0;
			number_of_lines++;
			lines = realloc(lines, number_of_lines * sizeof(line));
			if (lines == NULL) {
				perror("realloc error!");
				exit(EXIT_FAILURE);
			}
			last_alloc_dimension = -1;
			determines_duplicates(lines, number_of_lines);
		}else{
			if(counts_chars_on_one_line > last_alloc_dimension){
				if(last_alloc_dimension < 0){
					last_alloc_dimension = last_alloc_dimension * -1;
				}else{
					last_alloc_dimension = last_alloc_dimension * 2;
				}

				lines[number_of_lines -1].char_array = realloc(lines[number_of_lines -1].char_array, last_alloc_dimension * sizeof(char));
				if (lines[number_of_lines -1].char_array == NULL) {
					perror("realloc error!");
					exit(EXIT_FAILURE);
				}
			}
			lines[number_of_lines -1].char_array[counts_chars_on_one_line -1] = ch;
			lines[number_of_lines -1].length_char_array = counts_chars_on_one_line;

		}
		ch = getchar();
		counts_chars_on_one_line++;
	}

	putchar('\n');
	return EXIT_SUCCESS;
}

void determines_duplicates(line *lines, int number_of_lines){
	int righe_fa = 1;
	for(int i=number_of_lines - 3 ; i>=0 ; i--){
		if(compare_array( 	lines[number_of_lines -2].char_array,
							lines[number_of_lines -2].length_char_array,
							lines[i].char_array,
							lines[i].length_char_array)
						){
			printf("***questa riga è stata già letta %d righe fa***\n", righe_fa);
		}
		righe_fa++;
	}
}

int compare_array(char *char_array1, int length_char_array1 ,char *char_array2, int length_char_array2){
	if(length_char_array1 != length_char_array2){
		return FALSE;
	}
	for(int i=0 ; i<length_char_array1 ; i++){
		if(char_array1[i] != char_array2[i]){
			return FALSE;
		}
	}
	return TRUE;
}

