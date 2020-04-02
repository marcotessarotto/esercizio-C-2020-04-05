/** ex 2020-04-05 */
#include <stdio.h>
#include <string.h>

#define LTU_CHUNK 10
#define STR_CHUNK 100

int main(int argc, char **argv) {

	// Dynamic stacked list
	int mx_size = 0, mx_len = 0;
	char **mx = NULL;
	// Synamic stacked string
	int str_size = 0, str_len = 0;
	char *str = NULL;

	char next;

	while((next = getchar()) != EOF) {
		if (next == '\n') {
			// mx_buff expand if required
			if (mx_len + 1 > mx_size) {
				// alloc
				char ** n_mx = malloc(sizeof(char *) * (mx_len + LTU_CHUNK));
				if (n_mx == NULL) {
					printf("Error at malloc 1\n");
					exit(-1);
				}
				// clone if present
				if (mx != NULL) {
					memcpy(n_mx, mx, mx_len);
				}
				mx_size += LTU_CHUNK;
				mx = n_mx;
			}
			// Finalize current line
			str[str_len] = '\0';

			/* test point
			printf(":: ");
			for (int i = 0; i < mx_len; i++) {
				printf("%s ", mx[mx_len - 1 - i]);
			}
			printf("\n:: %s\n", str); */

			// Exercise check
			for (int i = 0; i < mx_len; i++) {
				if (strcmp(str, mx[mx_len - 1 - i]) == 0) {
					printf("***questa riga è stata già letta %d righe fa***\n", i + 1);
				}
			}

			// Move string to tree
		    mx[mx_len] = str;
			mx_len ++;
			// Clear string
			str = NULL;
			str_len = 0;
			str_size = 0;
		} else {
			// str_buff expand (keep allways space for next \0
			if (str_len + 2 > str_size) {
				// alloc
				char * n_str = malloc(sizeof(char) * (str_size + STR_CHUNK));
				if (n_str == NULL) {
					printf("Error at malloc 2\n");
					exit(-1);
				}
				// clone if present
				if (str != NULL) {
					memcpy(n_str, str, str_size);
				}
				str_size += STR_CHUNK;
				str = n_str;
			}
			// assign
			str[str_len] = next;
			str_len ++;
		}
	}
}

