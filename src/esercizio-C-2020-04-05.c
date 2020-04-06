#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* parseRaw(char *rawString, int rawNumber);

int main(int argc, char **argv) {
	int c;
	int size = 1;
	int rawNumber = 0;

	char *str;
	str = malloc(sizeof(char) * size);
	printf("I: ");
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			rawNumber++;
			str[size - 1] = c;
			size++;
			str = realloc(str, sizeof(char) * (size));
			if (str == NULL) {
				printf("realloc error!\n");
				exit(EXIT_FAILURE);
			}
			if (rawNumber > 1) {
				char *raw = parseRaw(str, rawNumber);
				for (int i = 0; i < rawNumber - 1; i++) {
					if (strcmp(raw, parseRaw(str, i)) == 0) {
						printf("***Questa riga è stata già letta alla riga %d***\n",i);
					}
				}
			}
			printf("I: ");
		} else {
			str[size - 1] = c;
			size++;
			str = realloc(str, sizeof(char) * (size));

		}

	}

	return 0;
}

char* parseRaw(char *rawString, int rawNumber) {
	int rowIndex = rawNumber - 1;

	char separator[] = "\n";
	char *rowCopy = strdup(rawString);

	char *row = strtok(rowCopy, separator);

	while (rowIndex > 0) {
		row = strtok(NULL, separator);
		rowIndex--;
	}

	return row;
}

/*
 scrivere un programma che legge da stdin una riga alla volta (la riga si considera terminata dal carattere \n).

 la lunghezza della riga è arbitraria, non fare ipotesi sulla massima lunghezza di riga.
 [in questo esercizio, occorre immagazzinare l'intera riga ed anche le precedenti].

 confrontare la riga appena letta con tutte le precedenti righe lette:
 il confronto parte dalla penultima riga e va a ritroso fino alla prima riga letta.

 se la riga appena letta ha un precedente, scrivere su stdout il messaggio
 "***questa riga è stata già letta %d righe fa***", dove viene indicata la posizione relativa della riga identica rispetto alla riga attuale
 (può accadere che una riga si ripresenti più di una volta; scrivere tutte le volte
 che si ripresenta)

 il programma termina in caso di EOF su stdin.

 esempio, I: significa input proveniente da stdin, O: indica l'output del programma su stdout

 I: xyz0000
 I: 1234
 I: 0000
 I: zzzzz
 I: 1234
 O: ***questa riga è stata già letta 3 righe fa***
 I: abcdefg
 I: 1234
 O: ***questa riga è stata già letta 2 righe fa***
 O: ***questa riga è stata già letta 5 righe fa***
 *
 * */

