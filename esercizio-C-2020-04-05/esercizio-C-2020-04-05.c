#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int contarighe=0;

typedef
		struct {
			char * riga;
			int lunghezza;
			} stringhe;

stringhe * righe;

void checklines(char * line, int length){

	int check =0;
	int contatore;

	if(contarighe>=1){

		for(int i=0; i<contarighe; i++){

			if(righe[i].lunghezza == length){

			contatore = memcmp(righe[i].riga, line, length*sizeof(char));

			if(contatore == 0){
				check = contarighe-i;
				printf("Questa riga è apparsa %d righe fa\n", check);
				}
			}
		}
	}
}

void checkmalloc(void * qualcosa){
	if(qualcosa == NULL){
			perror("malloc()");
			exit(EXIT_FAILURE);
		}
}

void checkrealloc(void * qualcosa){
	if(qualcosa == NULL){
			perror("realloc()");
			exit(EXIT_FAILURE);
		}
}

int main(){

	int c;
	int contachar=0;
	int stdline = 10;

	righe = malloc(1*sizeof(stringhe));
	checkmalloc(righe);

	char * riga;

	riga = malloc(stdline*sizeof(char));
	checkmalloc(riga);

	while((c=getchar()) != EOF){


		if(c != '\n'){
			riga[contachar] = (char)c;

			contachar++;
			if(contachar>=stdline){

				stdline = stdline*2;
				riga = realloc(riga, stdline*sizeof(char));
				checkrealloc(riga);
			}
		}

		if(c == '\n'){

		righe = realloc(righe,(contarighe+1)*sizeof(stringhe));
		checkmalloc(righe);

		righe[contarighe].lunghezza = contachar;

		righe[contarighe].riga = malloc((contachar)*sizeof(char));

		memcpy(righe[contarighe].riga, riga, contachar*sizeof(char));

		checklines(riga, contachar);

		if(memset(riga, 0, stdline*sizeof(char)) == NULL){
			perror("memset()");
			exit(EXIT_FAILURE);
		}

		contarighe++;
		contachar=0;
		}

	}

	printf("\n\nHo ricevuto EOF, termino!\n");

return 0;

}
