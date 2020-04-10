/*
 * esercizio-C-2020-04-05.c
 *
 *  Created on: Apr 2, 2020
 *      Author: marco
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char inputChar;
	int arrayLength = 5;
	char *char_array = calloc(arrayLength, sizeof(char));
	int index = 0;
	while ((inputChar = getchar()) != EOF) {
		if (index == arrayLength - 1) {
			arrayLength = arrayLength * 2;
			if (realloc(char_array, arrayLength) == NULL) {
				perror("realloc error!");
				exit(EXIT_FAILURE);
			}
		}
		char_array[index]=inputChar;
		index++;
	}
	free(char_array);
	return 0;
}

