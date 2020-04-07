#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>



typedef struct {
   int length; // lunghezza riga
   char * row; // puntatore alla riga
} row_type;



row_type * create_row_type(char * row,int length){

	row_type * new_row=malloc(sizeof(row_type));

	(*new_row).length=length;

	(*new_row).row=malloc(length*sizeof(char));

	strcpy((*new_row).row,row);

	return new_row;
}


void stampa_riga(row_type * row){
	for (int i=0;i<(*row).length;++i)
		printf("%c",(*row).row[i]);
	printf("");
}


void stampa_righe(row_type ** array,int n){
	for(int i=0;i<n;++i){
		printf("[riga %d]\t",i+1);
		stampa_riga(array[i]);
		printf("\n");
	}
}


void precedenti (row_type ** rows,char * row,int n){
	for (int i=0;i<n;++i)
		if(strcmp((*rows[i]).row,row)==0)
			printf("***questa riga è già stata letta %d righe fa***\n",n-i);

}





int main(int argc, char **argv) {

	//array contenente tutte le righe
	row_type ** all_rows;
	all_rows=(row_type **)malloc(sizeof(row_type));

	int n_rows=0;
	char c;
	int counter=0;
	char * new_row;

	new_row=malloc(sizeof(char));

	while((c=getchar())!=EOF){

		if(c!='\n'){ //aggiungo i caratteri all'array contenente la riga corrente
			counter++;
			new_row=realloc(new_row,counter*sizeof(char));
			new_row[counter-1]=c;

		}
		else if(counter!=0){ //se counter=0 ho letto solo un '\n' per questa riga, non devo salvarla

			// aggiungo la riga appena letta all'array contenente le righe
			//e aumento il contatore delle righe
			all_rows[n_rows] = create_row_type(new_row,counter);
			++n_rows;
			all_rows=(row_type **)realloc (all_rows,n_rows * sizeof(row_type));

			//guardo se ci sono precedenti confrontando le (n_rows-1) righe precedenti
			precedenti(all_rows,new_row,n_rows-1);

			//reinizializzo variabili di appoggio
			new_row=malloc(sizeof(char));
			counter=0;
		}
	}

}
