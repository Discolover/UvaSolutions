#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int greatthan[26][26];
char VARS[21];
char *VAR;
int inuse[26];

char nonspace()
{
	char c;

	while ((c = getchar()) == ' ')
		;

	return c;
}

int cmpfunc(const void * a, const void * b) {
   return (*(char*)a - *(char*)b);
}

void createcand(char *cand)
{
	int i, gt;
	char *v;

	for (v = VARS; *v != '\0'; ++v) {
		gt = 0;
		if (inuse[*v - 'a']) continue;
		for (i = 0; i < 26; ++i) {
			if (inuse[i]) continue;
			if (greatthan[*v - 'a'][i]) {
				gt = 1;
				break;
			}
		}
		if (!gt) {
			/*printf(">> %c\n", *v);*/
			*cand++ = *v;
		}
	}
	*cand = '\0';
	/*printf("\n");*/
}

void bt(char a[], int k)
{
	char cand[21];
	char *p;

	if (VARS[k] == '\0') {
		printf("%s\n", a);
		return;
	}

	p = cand;
	createcand(p);
	
	for (; *p != '\0'; ++p) {
		a[k] = *p;
		inuse[*p - 'a'] = 1;
		bt(a, k+1);
		inuse[*p - 'a'] = 0;
	}	
}

int main()
{
	char *v;
	char c;
	char a[21];

	while (1) {
		v = VARS;
		while ((*v = nonspace()) != '\n')
			++v;
		*v = '\0';
		qsort(VARS, strlen(VARS), sizeof *VARS, cmpfunc);

		while (((c = nonspace()) != '\n') && (c != EOF)) {
			greatthan[nonspace() - 'a'][c - 'a'] = 1;
		}

		VAR = VARS;
		memset(a, '\0', sizeof a);
		bt(a, 0);

		memset(greatthan, 0, sizeof greatthan);

		if ((c = getchar()) == EOF) break;
		ungetc(c, stdin);
		printf("\n");
	}

	return 0;
}
