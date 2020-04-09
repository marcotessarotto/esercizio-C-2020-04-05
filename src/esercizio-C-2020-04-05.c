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


void compare_lines(line * lines, int number_of_lines);
int compare_array(char *char_array1, int length_char_array1 ,char *char_array2, int length_char_array2);
//void print_line(line lines); //for TEST only

int main(int argc, char *argv[]) {

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
			compare_lines(lines, number_of_lines);
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
	/* for TEST only
	for(int i=0 ; i<number_of_lines ; i++){
		print_line(lines[i]);
	}
	*/
	putchar('\n');
	return EXIT_SUCCESS;
}

void compare_lines(line *lines, int number_of_lines){
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

/* for TEST only
void print_line(line lines){
	if(lines.char_array != NULL){
		printf("[");
		for( int i=0 ; i<lines.length_char_array ; i++){
			printf("%c ", lines.char_array[i]);
		}
		printf("]\n");
	}
}
*/
