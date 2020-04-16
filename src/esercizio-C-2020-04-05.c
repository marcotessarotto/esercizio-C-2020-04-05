//non capendo il motivo mi copia in 'righe' sempre la stessa parola

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef
	struct {
		char *str[MAX];
} string;

string *righe;
int x = 0;

void toknize(char* array, int n){

	righe->str[n]= array;
	
	int result;
	int count =1;
	for(int i = 0; i<n ; i++){
		if(i != n){
			result = strcmp(righe->str[n], righe->str[i]);
				if (result == 0){
				printf("questa riga è stata già letta %d righe fa\n", count);
			}
			count++;
		}
	}


	
}

int main(int argc, char *argv[]) {
	righe = calloc(MAX ,MAX * sizeof(string));
	int segnale;
	char *char_array;
	char_array = calloc(MAX, MAX * sizeof(int));

		if (char_array == NULL) {
					perror("calloc error!");
					exit(EXIT_FAILURE);
		}
		int i = 0;
		int n = 0;
		while((segnale = getchar()) != EOF){

			if(segnale != '\n'){
				char_array[i] = segnale;
				i++;
			}
			if(segnale == '\n'){
				char_array[i] = segnale;
				i=0;

				toknize(char_array, n);
				n++;
				memset(char_array, 0, MAX* sizeof(char));

			}

		}

}

