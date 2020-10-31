#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 76
typedef unsigned int ui;

int A[N * N];

int FULL[N * N * 4];

#define at(ARRAY, I, J, NCOLS) (ARRAY[(I) * (NCOLS) + (J)])

int rect(ui i, ui j, ui n, ui m, int *rect, int nc) {
    int ans;

    ans = at(rect, n, m, nc);
    if (i) ans -= at(rect, i - 1, m, nc);
    if (j) ans -= at(rect, n, j - 1, nc);
    if (j && i) ans += at(rect, i - 1, j - 1, nc);

    return ans;
}

void print(int *arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
	for (int j = 0; j < m; ++j) {
	    printf("%3d ", at(arr, i, j, m));
	}
	printf("\n");
    }
}

void transform(int *arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
	for (int j = 0; j < m; ++j) {
	    if (i != 0)
		at(arr, i, j, m) += at(arr, i - 1, j, m);
	    if (j != 0)
		at(arr, i, j, m) += at(arr, i, j - 1, m);
	    if (i && j)
		at(arr, i, j, m) -= at(arr, i - 1, j - 1, m);
	}
    }
}

int find_max_rect(int *arr, int n, int m) {
    int max = -100 * 75 * 75 - 1, tmp;

    for (int i = 0; i < n; ++i) {
	for (int j = 0; j < n; ++j) {
	    for (int x = i; x < n + i; ++x) {
		for (int y = j; y < n + j; ++y) {
		    /* printf("(%d, %d) - (%d, %d)\n", i, j, x, y); */
		    tmp = rect(i, j, x, y, arr, m);
		    if (tmp > max) {
		        max = tmp;
		    }
		}
	    }
	}
    }

    /* printf("max: %d\n", max); */
    /* printf("%d %d %d %d\n", a, b, c, d); */

    return max;
}


int main() {

    int tc, n;

    scanf("%d", &tc);

    while (tc--) {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < n; ++j) {
		scanf("%d", &at(A, i, j, n));
	    }
	}

	for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < n; ++j) {
		at(FULL, i, j, n*2) = at(A, i, j, n);
		at(FULL, i, j+n, n*2) = at(A, i, j, n);
		at(FULL, i + n, j, n*2) = at(A, i, j, n);
		at(FULL, i + n, j + n, n*2) = at(A, i, j, n);
	    }
	}

	/* print(FULL, n*2, n*2); */
	/* printf("\n"); */

	transform(FULL, n*2, n*2);

	/* print(FULL, n*2, n*2); */

	printf("%d\n", find_max_rect(FULL, n, n*2));
    }


    return 0;

}
