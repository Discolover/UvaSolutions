#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXV (26 + 10 + 2)
#define S 0
#define T 37
#define INF 38

/* 0 s; 1 - 26 apps; 27 - 36 computers; 37 t */
int RES[MAXV][MAXV];
int VISITED[MAXV];
int QUEUE[MAXV];
int PARENT[MAXV];
char ANS[10];
int TOTAL_USRS;

void path_bfs()
{
	int *h, *t, v1, v2;

	h = t = QUEUE;
	VISITED[S] = 1;
	*t++ = S;

	while (t - h) {
		v1 = *h++;
		/* printf(":%d\n", v1); */
		if (v1 == T) break;
		for (v2 = 0; v2 < MAXV; ++v2) {
			if (RES[v1][v2] && !VISITED[v2]) {
				*t++ = v2;	
				VISITED[v2] = 1;
				PARENT[v2] = v1;
			}
		}
	}
}

int augment()
{
	int v, p;
	int minf = INF;

	for (v = T; v; v = p) {
		p = PARENT[v];
		if (RES[p][v] < minf) minf = RES[p][v];	
	}
	for (v = T; v; v = p) {
		p = PARENT[v];
		RES[p][v] -= minf;
		RES[v][p] += minf;

		if (27 <= v && v <= 36 && !RES[p][v])
			ANS[v - 27] = p - 1 + 'A';
	}
	return minf;
}

void solve()
{
	int flow = 0, i;

	for (;;) {
		memset(VISITED, 0, sizeof VISITED);
		memset(QUEUE, 0, sizeof QUEUE);
		memset(PARENT, 0, sizeof PARENT);

		path_bfs();			

		if (PARENT[T])
			flow += augment();
		else
			break;
	}

	if (TOTAL_USRS != flow) {
		printf("!\n");
		return;
	}

	for (i = 0; i < 10; ++i) {
		printf("%c", (ANS[i]) ? ANS[i] : '_');
	}
	printf("\n");
}

int main()
{
	#define N 16
	char line[N];
	int app, nusr, srv, ch, i;

	for (i = 0; i < 10; ++i) RES[i + 27][T] = 1;

	while (fgets(line, N, stdin)) {
		if (line[0] == '\n') {
			memset(RES, 0, sizeof RES);
			memset(ANS, 0, sizeof ANS);
			TOTAL_USRS = 0;
			for (i = 0; i < 10; ++i) RES[i + 27][T] = 1;
			continue;
		}
		app = line[0] - 'A' + 1;
		nusr = line[1] - '0';
		TOTAL_USRS += nusr;
		RES[0][app] = nusr;
		/* printf("%c %d\n", app + 'A' - 1, nusr); */
		for (i = 3; line[i] != ';'; ++i) {
			srv = line[i] - '0' + 27;
			/* printf("%d\n", srv - 27); */
			RES[app][srv] = 1;
		}
		ch = getc(stdin);
		if (ch == '\n' || ch == EOF) {
			solve();
		}
		ungetc(ch, stdin);
	}

	return 0;
}
