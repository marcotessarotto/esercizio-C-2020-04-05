/*scrivere un programma che legge da stdin una riga alla volta (la riga si considera terminata dal carattere \n).

la lunghezza della riga è arbitraria, non fare ipotesi sulla massima lunghezza di riga.
[in questo esercizio, occorre immagazzinare l'intera riga ed anche le precedenti].

confrontare la riga appena letta con tutte le precedenti righe lette:
il confronto parte dalla penultima riga e va a ritroso fino alla prima riga letta.

se la riga appena letta ha un precedente, scrivere su stdout il messaggio
"***questa riga è stata già letta %d righe fa***", dove viene indicata la posizione relativa della riga identica rispetto alla riga attuale
(può accadere che una riga si ripresenti più di una volta; scrivere tutte le volte
che si ripresenta)

il programma termina in caso di EOF su stdin.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//controlla se la riga non sia già stata inserita
int controllapresenza(char * riga, char** storico, unsigned int nrighe){
	if((riga==NULL) || (storico==NULL)){
		return 1;
	}
	int posizione;
	for(int t=(nrighe-2); t>=0; t--){
		if(strcmp(riga, storico[t])==0){
			posizione=nrighe-t-1;
			printf("***questa riga è stata già letta %d righe fa***\n", posizione);
		}
	}
	return 0;
}


//aggiunge la riga letta allo storico e libera la memoria occupata dall'ultima riga letta per leggere la successiva
int aggiungiriga(char * riga, unsigned int lunghezza_riga, char** storico, unsigned int indice_storico){
	if((riga==NULL) || (storico==NULL)){
		return 1;
	}
	//"trasformo" array di caratteri in stringa
	riga[lunghezza_riga]='\0';
	//copio la riga appena letta nello storico
	storico[indice_storico]=strdup(riga);
	//libero la memoria occupata dall'ultima riga così da leggere la successiva
	free(riga);
	riga=malloc(sizeof(char));
	if(riga==NULL){
		return 1;
	}
	return 0;
}


int main(int argc, char *argv[]) {

	char c;
	unsigned int c_counter=0;
	unsigned int riga_counter=0;

	char * * riga_array;
	riga_array=malloc(sizeof(char *));
	if(riga_array==NULL){
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	char * riga;
	riga=malloc(sizeof(char));
	if(riga==NULL){
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	while((c=getchar())!=EOF){
		if(c=='\n'){
			if(aggiungiriga(riga, c_counter, riga_array, riga_counter)!=0){
				perror("aggiungiriga error!");
				exit(EXIT_FAILURE);
			}
			riga_counter++; //aumento il contatore delle righe lette
			c_counter=0; //azzero il contatore di caratteri della riga
			//confronto con le righe precedenti
			if(controllapresenza(riga_array[riga_counter-1], riga_array, riga_counter)!=0){
				perror("controllapresenza error!");
				exit(EXIT_FAILURE);
			}
			riga_array=realloc(riga_array, (riga_counter+1)*sizeof(char *));
			if(riga_array==NULL){
				perror("realloc error!");
				exit(EXIT_FAILURE);
			}
		}
		else{
			riga[c_counter]=c;
			c_counter++;
			riga=realloc(riga, (c_counter+1)*sizeof(char));
			if(riga==NULL){
				perror("realloc error!");
				exit(EXIT_FAILURE);
			}
			//alla fine dell'esle mi trovo con un array di caratteri contenente la riga
		}
	}
	return 0;
}

