#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

char * prendi_riga(char * string_tot, int n );
void confronta_riga(char * string_tot, int n);


void confronta_riga(char * string_tot, int n){

	char * riga_att;
	riga_att = prendi_riga(string_tot, n);
	printf("%s\n", riga_att);
	for(int i = n-1; i > 0; i--){
		char * rig_i = prendi_riga(string_tot, i);
		if ( strcmp(riga_att, rig_i) == 0){
			printf("***questa riga è già stata letta %d righe fa***\n", (n-i));
		}

	}
}



char * prendi_riga(char * string_tot, int n ){

	char sep[] = "\n";
	char * token;
	char * dup_str;

	dup_str = strdup(string_tot);

	token = strtok(dup_str, sep);

	while (n > 1) {
		token = strtok(NULL, sep);
		n--;
	  }

	return token;
}



int main(int argc, char *argv[]) {

	int c;
	int num_string=0;
	char * str = calloc(1, sizeof(char));
	int tot_size = 1;

	while ((c = getchar()) != EOF){

		str[tot_size-1] = c;
		tot_size++;
		str = realloc(str, tot_size*sizeof(char));

		if(c == '\n'){

			num_string++;
			str[tot_size-1] = '\0';

			confronta_riga(str, num_string);

		}

	}

	printf("Ciao ciao!");
	free(str);
	return 0;
}

