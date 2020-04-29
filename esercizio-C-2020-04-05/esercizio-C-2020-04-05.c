#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

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

	if(contarighe>1){

		for(int i=0; i<contarighe; i++){

			if(length == righe[i].lunghezza && line[0] == righe[i].riga[0]){

				contatore=0;

				for(int j=1; j<righe[i].lunghezza; j++){

					if(line[j] == righe[i].riga[j])
					contatore++;
				}

				if(contatore == length){
					check = contarighe-i;
					printf("Questa riga è apparsa %d righe fa\n", check);
					return;
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

			if(contarighe>1){

				righe = realloc(righe, contarighe*(sizeof(stringhe)));
				checkrealloc(righe);

			}

		righe[contarighe].lunghezza = contachar-1;

		righe[contarighe].riga = malloc((contachar-1)*sizeof(char));

		for(int i=0; i<contachar; i++){

			righe[contarighe].riga[i] = riga[i];
		}

		checklines(riga, contachar);

		free(riga);

		riga = malloc(stdline*sizeof(char));
		checkmalloc(riga);

		contarighe++;
		contachar=0;
		}

	}

return 0;

}
