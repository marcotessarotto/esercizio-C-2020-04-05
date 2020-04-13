#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_ptr(void *ptr)
{
	if (ptr == NULL) {
		puts("Memory allocation error");
		exit(EXIT_FAILURE);
	}
}

void compare(char **str_arr, int index)
{
	for (int i = index - 1; i >= 0; i--) {
		if (!strcmp(str_arr[index], str_arr[i]))
			printf("***questa riga è stata già letta %d righe fa***\n", index - i);
	}
}

int main(int argc, char* argv[])
{
	char c;
	char *new_string;
	int str_index = 0, char_index = 0;
	char **input = calloc(1, sizeof(char*));
	char **new_arr;
	check_ptr(input);

	puts("Waiting for input (trigger EOF to quit)...");

	while ((c = getchar()) != EOF) {
		if (c != '\n') {
			new_string = realloc(input[str_index], (char_index + 1) * sizeof(char));
			check_ptr(new_string);
			input[str_index] = new_string;
			input[str_index][char_index] = c;
			char_index++;
		} else {
			char_index = 0;
			compare(input, str_index);
			str_index++;
			new_arr = realloc(input, (str_index + 1) * sizeof(char*));
			check_ptr(new_arr);
			input = new_arr;
			input[str_index] = calloc(1, sizeof(char));
			check_ptr(input[str_index]);
		}
	}

	return 0;
}
