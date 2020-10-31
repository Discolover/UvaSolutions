#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define INF DBL_MAX

struct point {
    int x, y;
} PNT[8];

double DIST[8][8], FIN_DIST[8][8];
int FIN_PATH[8];

double dist(int a, int b) {
    struct point p1 = PNT[a], p2 = PNT[b];
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y-p1.y));
}

double FIN_LEN, CUR_LEN;
int SET, N;

void print() {
    for (int i = 1; i < N; ++i) {
	int a = FIN_PATH[i - 1], b = FIN_PATH[i];
	printf("Cable requirement to connect"
		" (%d,%d) to (%d,%d) is %.2f feet.\n"
		, PNT[a].x, PNT[a].y , PNT[b].x, PNT[b].y
		, FIN_DIST[a][b] + 16);
    }
    printf("Number of feet of cable required is %.2f.\n", FIN_LEN + 16 * (N-1));
}

void bt(int path[], int k) {
    if (k == N) {
	if (CUR_LEN < FIN_LEN) {
	    FIN_LEN = CUR_LEN;
	    memcpy(FIN_DIST, DIST, sizeof DIST);
	    memcpy(FIN_PATH, path, sizeof FIN_PATH);

	    //print();
	}

	return;
    }

    for (int i = 0; i < N; ++i) { //<
	double d;
	if (!(SET & 1 << i) &&
	    (k == 0 || (CUR_LEN + (d = dist(path[k-1], i)) < FIN_LEN))) {
	    SET |= 1 << i;
	    path[k] = i;
	    if (k) { //<
		DIST[path[k-1]][i] = d;
		DIST[i][path[k-1]] = DIST[path[k-1]][i];
		CUR_LEN += DIST[path[k-1]][i];
	    }

	    bt(path, k + 1);

	    SET ^= 1 << i;
	    //path[k] = 0;
	    if (k) { //<
		CUR_LEN -= DIST[path[k-1]][i];
		DIST[path[k-1]][i] = 0;
		DIST[i][path[k-1]] = 0;
	    }
	}
    }
}

void slv() {
    int path[8] = {0};

    path[0] = 0;
    SET = 0; // <
    FIN_LEN = INF;
    CUR_LEN = 0;
    memset(DIST, 0, sizeof DIST);

    bt(path, 0); //<
    print();

    //printf("path:\n");
    //for (int i = 0; i < N; ++i) {
    //    printf("%d", path[i]);
    //}
    //printf("\n");
    //printf("DIST:\n");
    //for (int i = 0; i < N; ++i) {
    //    for (int j = 0; j < N; ++j) {
    //        printf("%f", DIST[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("\n");
}

int main() {
    int tc = 1;
    while (scanf("%d", &N) && N) {
	printf("**********************************************************\n");
	printf("Network #%d\n", tc++);
	for (int i = 0; i < N; ++i) {
	    scanf("%d %d", &PNT[i].x, &PNT[i].y);
	}
	slv();
    }

    return 0;
}
