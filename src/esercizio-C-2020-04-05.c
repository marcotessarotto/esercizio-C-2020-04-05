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
void verify_row(char ** tot, int length, int counter);

unsigned int rows_counter = 0;

int main(int argc, char *argv[]) {
	int c;
	unsigned int char_counter = 0;
	unsigned int size = 1;

	char * row;
	char ** all_rows;

	row = calloc(size, sizeof(char));
	all_rows = calloc(size, sizeof(char *));

	if ((row == NULL) || (all_rows == NULL)) {
		perror("calloc error\n");
		exit(EXIT_FAILURE);
	}

	printf("Insert text: ");

	while ((c = getchar()) != EOF) {

		if (c == '\n') {
			rows_counter++;
			all_rows = realloc(all_rows, rows_counter * sizeof(char *));

			if (all_rows == NULL) {
				perror("realloc error\n");
				exit(EXIT_FAILURE);
			}

			memcpy(&(all_rows[rows_counter-1]), row, size * sizeof(char));
			verify_row(all_rows, size, rows_counter);

			size = 0;
			char_counter = 0;
			printf("\nInsert text: ");
		} else {
			row[char_counter] = c;
			size++;
			row = realloc(row, size * sizeof(char));
			if (row == NULL) {
				perror("realloc error\n");
				exit(EXIT_FAILURE);
			}
			char_counter++;
		}
	}

	free(all_rows);

	exit(EXIT_SUCCESS);
}

void verify_row(char ** rows, int size, int num_of_rows) {
    int index_row = num_of_rows - 1;
    for (int i = num_of_rows - 2; i >= 0; i--){
        int check = memcmp(&(rows[index_row]), &(rows[i]), size * sizeof(char));
        if (check == 0){
            int find_at = index_row - i;
            printf("\n***questa riga è stata già letta %d righe fa***\n", find_at);
        }
    }
}

