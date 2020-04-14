/*
 * esercizio-C-2020-04-05.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Spopoi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;
	int length;
} array;

char* reallocCharArray(char *array, int length) { //method to realloc a dynamic array
	char *puntatore = realloc(array, length);
	if (puntatore == NULL) {
		perror("realloc error!");
		exit(EXIT_FAILURE);
	} else
		array = puntatore;
	return array;
}

short compareCharArray(char *array, int endFirst, int beginFirst,
		int beginSecond, int endSecond) {
	if (endSecond - beginSecond != endFirst - beginFirst)
		return -1;
	for (int i = 0; i < endFirst - beginFirst; i++) {

		if (array[i + beginFirst] != array[i + beginSecond])
			return -1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	char inputChar;
	int index = 0;
	array char_array; //inizialization of typedef 'array'
	char_array.length = 5;
	char_array.name = calloc(char_array.length, sizeof(char));

	int indexOfBeginNewLine[50]; //inizialization array of int which contains index of character new line in char_array
	int numberOfLines = 1;		//i chose a static array in order to semplify the implementation of this exercise
	memset(indexOfBeginNewLine, 0, 50 * sizeof(int));

	while ((inputChar = getchar()) != EOF) {

		if (index == char_array.length - 1) { //condition for realloc char_array
			char_array.name = reallocCharArray(char_array.name,
					char_array.length * 2);
		}
		if (inputChar == '\n') { //creation of new line and comparison with previous lines
			indexOfBeginNewLine[numberOfLines] = index;
			for (int i = numberOfLines - 1; i > 0; i--) { //for each previous line
				if (compareCharArray(char_array.name, indexOfBeginNewLine[i],
						indexOfBeginNewLine[i - 1],
						indexOfBeginNewLine[numberOfLines - 1],
						indexOfBeginNewLine[numberOfLines]) == 0) { //comparing the two string giving to compareCharArray both indexes of begin and end of lines
 					printf("***questa riga è stata già letta %d righe fa***\n",
							numberOfLines - i);
				}
			}
			numberOfLines++;

		} else {
			char_array.name[index] = inputChar;
			index++; //new character
		}
	}
	free(char_array.name);
	return 0;
}
