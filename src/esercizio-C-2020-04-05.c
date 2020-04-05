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

esempio:

xyz0000
1234
0000
zzzzz
1234
abcdefg
1234
***questa riga è stata già letta 2 righe fa***
***questa riga è stata già letta 5 righe fa***

 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verify(char ** array, int dim)
{
	for(int i=dim-2; i>=0; i--)
	{
		if(memcmp(&(array[dim-1]), &(array[i]), dim * sizeof(char))==0)
			printf("questa riga è stata già letta %d righe fa\n", dim-i-1);
	}

}

int main(int argc, char *argv[]) {

int i=0,j=0,c;
unsigned int arraysize=1;

char * val = calloc(arraysize, sizeof(char));
char ** val_tot = calloc(arraysize, sizeof(char *));

	if (val == NULL || val_tot == NULL) {

		perror("calloc error!");
		exit(EXIT_FAILURE);
	}

	while((c=getchar())!= EOF)
		{

			if(c!='\n')
			{
				val[i]=c;
				arraysize++;
				val = realloc(val,(arraysize)*sizeof(char));
				i++;
			}
			else
			{
				j++;
				val_tot = realloc(val_tot,j*sizeof(char *));
				memcpy(&(val_tot[j-1]), val, arraysize * sizeof(char));

				verify(val_tot,j);
				//free(val)
        /*
        Qui vorrei deallocare la memoria di "val" ma mi da errore con il comando commentato.
        Funziona lo stesso con l'esempio nella consegna ma il problema si pone quando vengono inserite stringhe più lunghe e poi più corte.
        ----------------------------------------------------------------------------
        Es:
        ciao          val[]={c,i,a,o}
        ciaocomestai   val[]={c,i,a,o,c,o,m,e,s,t,a,i}
        bene            val[]={b,e,n,e,c,o,m,e,s,t,a,i}
        --------------------------------------------------------------------------------
        Questo perchè non risucendo a liberare "val" semplicemente sovrascrivo i dati.
        */
				arraysize=0;
				i=0;
        
			}

		}

  free(val);
  free(val_tot);
	return 0;
}


