#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void memorize_array(char * tot, char * array, int length, int counter) {
    memcpy(tot[counter-1], array, length * sizeof(char));
}

void control_reps(char * tot, int length, int counter) {
    int start = counter-1;
    for(int i=counter-2; i >= 0; i--){
        int check = memcmp(tot[start], tot[i], length * sizeof(char));
        if (check == 0){
            int rep = start - i;
            printf("\n***questa riga è stata già letta %d righe fa***\n", rep);
        }
    }
}

int main (int argc, char * argv []) {
    char input;
    int i = 0;
    int counter = 0;
    unsigned int length = 1;
    while((input = getchar()) != EOF){
        char * array_char = calloc(length, sizeof(char));
        char * tot_array = calloc(length, sizeof(* char));
        switch ()
        {
        case input != '\n':
            array_char[i] = input;
            length++;
            array_char = realloc(array_char, length * sizeof(char));
            i++;
            break;
        default input == '\n':
            counter++;
            tot_array = realloc(tot_array, counter * sizeof(* char));
            memorize_array(tot_array, array_char, length, counter);
            control_reps(tot_array, length, counter);
            free(array_char);
            length = 0;
            i = 0;
            break;
    }

    return 0;
}
