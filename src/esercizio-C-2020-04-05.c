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
				if (mx != NULL) {
					mx = malloc(sizeof(char *) * LTU_CHUNK);
				} else {
					mx = realloc(mx, sizeof(char *) * (mx_len + LTU_CHUNK));
				}
				if (mx == NULL) {
					printf("Error at malloc/realloc 1\n");
					exit(-1);
				}
				mx_size += LTU_CHUNK;
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
				if (str == NULL) {
					str = malloc(sizeof(char) * STR_CHUNK);
				} else {
					str = realloc(str, sizeof(char) * (str_size + STR_CHUNK));
				}
				if (str == NULL) {
					printf("Error at malloc/realloc 2\n");
					exit(-1);
				}
				str_size += STR_CHUNK;
			}
			// assign
			str[str_len] = next;
			str_len ++;
		}
	}
}

