#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <errno.h>

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
 */

char * get_row(char * rows, int n_rows);



int main(int argc, char *argv[]) {
	unsigned int rows_counter = 0;
	unsigned int length = 1;

	char * rows;

	rows = calloc(length, sizeof(char));

	if (rows == NULL) {
		perror("calloc error\n");
		exit(EXIT_FAILURE);
	}

	printf("Insert text: ");

	while ((rows[length - 1] = getchar()) != EOF) {
		if(rows[length - 1] == '\n'){
			rows_counter++;
			if (rows_counter > 1) {
				char * current_row = get_row(rows, rows_counter);
				for(int i = rows_counter - 1; i > 0; i--){
					if(strcmp(current_row, get_row(rows, i)) == 0) {
						if ((rows_counter - i) == 1)
							printf("***questa riga è stata già letta %d riga fa***\n", rows_counter - i);
						else
							printf("***questa riga è stata già letta %d righe fa***\n", rows_counter - i);
					}
				}
			}
			printf("Insert text: ");
		}

		length++;

		rows = realloc(rows, length * sizeof(char));

		if (rows == NULL) {
			printf("realloc error!\n");
			exit(EXIT_FAILURE);
		}
	}

	free(rows);

	exit(EXIT_SUCCESS);
}

char * get_row(char * rows, int n_rows) {
	char rows_sep[] = "\n";
	char *rows_cpy = strdup(rows);
	char *row;

	row = strtok(rows_cpy, rows_sep);
	n_rows--;

	while(n_rows > 0){
		row = strtok(NULL, rows_sep);
		n_rows--;
	}

	return row;
}

