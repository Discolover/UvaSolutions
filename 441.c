#include <stdio.h>

void ans(int S[], int k) {
    int i, j, a, b, x, y, q;
    int R[6];
    for (i = 0; i < k; ++i) {
	R[0] = S[i];
	for (j = i+1; j < k; ++j) {
	    R[1] = S[j];
	    for (a = j+1; a < k; ++a) {
		R[2] = S[a];
		for (b = a+1; b < k; ++b) {
		    R[3] = S[b];
		    for(x = b+1; x < k; ++x) {
			R[4] = S[x];
			for (y = x+1; y < k; ++y) {
			    R[5] = S[y];
			    printf("%d", R[0]);
			    for (q = 1; q < 6; ++q)
				printf(" %d", R[q]);
			    printf("\n");
			}
		    }
		}
	    }
	}
    }
}

int main()
{
    int k, i;
    int S[12];

    scanf("%d", &k);
    do {
	for (i = 0; i < k; ++i) {
	    scanf("%d", S + i);
	}
	ans(S, k);
    } while (scanf("%d", &k) && k && putchar('\n'));

    return 0;
}
