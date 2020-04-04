/*
 * esercizio-C-2020-04-05.c
 *
 *  Created on: Apr 2, 2020
 *      Author: marco
 */
/******TESTO ESERCIZIO**********
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
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * get_row(char * c, int n);	//funzione che restituisce la riga n-esima di in un vettore di caratteri

int main(int argc, char *argv[]) {
	char * c;
	int length = 1;	//contatore del numero di caratteri (+1)
	int n_rows = 0;	//contatore del numero di righe

	c = calloc(length, sizeof(char));

	if(c == NULL){
		printf("calloc ha fallito!\n");
		exit(1);
	}

	while ((c[length - 1] = getchar()) != EOF) {
		if(c[length -1] == '\n'){
			n_rows++;	//incremento il numero di righe totali
			if(n_rows > 1){	//faccio il controllo sulle righe precedenti solo se ce ne sono almeno 2
				char * last_row = get_row(c, n_rows);	//prendo l'ultima riga
				for(int i = n_rows - 1; i > 0; i--){	//scorro le righe dall'ultima alla prima
					if(strcmp(last_row,get_row(c, i)) == 0){	//confronto l'ultima riga con quella corrente
						printf("***questa riga è stata già letta %d righe fa***\n", n_rows - i);
					}
				}
			}
		}

		length++;	//incremento il numero di caratteri presi in input
		c = realloc(c, sizeof(char) * length);	//rialloco c così che possa ricevere un altro carattere in input
		if(c == NULL){	//controllo che il realloc non abbia avuto problemi
			printf("calloc ha fallito!\n");
			exit(1);
		}
	}

	free(c);

	return 0;
}

//NB: suppongo che i controlli su "n" siano fatti esternamente alla funzione (qualora ce ne sia la necessità)
char * get_row(char * c, int n){ 
	char s[] = "\n"; // caratteri separatori da utilizzare per la suddivisione
	char *token;
	char *temp;
	temp = strdup(c);	//duplico il vettore "c" così da non intaccarlo con la tokenizzazione

	token = strtok(temp, s);	//ottengo la prima riga inserita in input
	n--;

	//scorro fino alla riga n-esima
	while(n > 0){
		token = strtok(NULL, s);
		n--;
	}

	return token;
}

