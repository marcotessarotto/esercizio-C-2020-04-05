#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * scrivere un programma che legge da stdin una riga alla volta (la riga si considera terminata dal carattere \n).

la lunghezza della riga è arbitraria, non fare ipotesi sulla massima lunghezza di riga.
[in questo esercizio, occorre immagazzinare l'intera riga ed anche le precedenti].

confrontare la riga appena letta con tutte le precedenti righe lette:
il confronto parte dalla penultima riga e va a ritroso fino alla prima riga letta.

se la riga appena letta ha un precedente, scrivere su stdout il messaggio
"***questa riga è stata già letta %d righe fa***", dove viene indicata la posizione relativa della riga identica rispetto alla riga attuale
(può accadere che una riga si ripresenti più di una volta; scrivere tutte le volte
che si ripresenta)

il programma termina in caso di EOF su stdin.
*/

char *getRow(char * ch, int lines);

int main(int argc, char *argv[]){
	unsigned int lines_counter = 0;
	unsigned int char_counter = 1;
	char *ch;
	//char *stringa;
	//char *token;
	//char s[] = "\n";


	printf("Inserisci  stringa:\n");
	ch= malloc(sizeof(char));
	if (ch == NULL){
		perror("malloc ha fallito");
		return -1;
	}

	while( ( ch[char_counter-1]= getchar()) != EOF){
		if( ch[char_counter-1] == '\n'){
			lines_counter++;
			if(lines_counter > 1){
				char * copia = getRow(ch, lines_counter);
				for( int i=1; i<lines_counter; i++){
					if (strcmp(copia, getRow(ch, i)) == 0 ){
						printf("O: Ho già letto questa riga %d fa\n", lines_counter-i);
					}

				}
			}
		}
		char_counter++;
		ch = realloc(ch, char_counter*sizeof(char));
		if( ch == NULL){
			perror("realloc ha fallito");
			return -1;
		}
	}


	free(ch);
	return 0;
}

char *getRow(char * ch, int lines){
	char s[] = " \n";
	char *str;
	char * token;

	str = strdup(ch);
	token = strtok(str, s);
	lines--;

	while ( lines > 0 ) {
		token = strtok(NULL, s);
		lines--;
	}

	return token;
}



