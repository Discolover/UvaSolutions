#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define UNSEEN 2

int G[200][200];
int Q[200];
int val[200];

int isbiclrd(int nd, int n)
{
	int i, *qh, *qt;
	int bicolored = 1;

	qh = qt = Q;

	*qt++ = nd;
	val[nd] = 0;

	while (qh != qt) {
		nd = *qh++;
		/* printf("nd: %d\n", nd); */
		for (i = 0; i < n; ++i) {
			if (!G[nd][i]) continue;
			/* printf("%d ", i);	*/
			if (val[i] == UNSEEN) {
				val[i] = 1 - val[nd];
				*qt++ = i;
			} else if (val[i] == val[nd]) {
				bicolored = 0;
				break;
			}	
		}
		/* printf("\n"); */
		if (!bicolored) break;
	}

	return bicolored;
}

int main()
{
	int n, l;
	int a, b;

	while (scanf("%d", &n) && n) {
		for (a = 0; a < n; ++a)
			for (b = 0; b < n; ++b)
				G[a][b] = 0;
		for (a = 0; a < n; ++a) val[a] = UNSEEN;
		scanf("%d", &l);
		while (l--) {
			scanf("%d %d", &a, &b);
			G[a][b] = 1;
			G[b][a] = 1;
		}
		printf("%s.\n", isbiclrd(a, n) ? "BICOLORABLE" : "NOT BICOLORABLE");
	}
	return 0;
}
