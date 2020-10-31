#include <stdio.h>
#include <math.h>
#include <cstring>

int N;
int ring[16];
int his[16 + 1];

bool is_prime(int num) {
    int n = (int)sqrt(num);

    for (int i = 2; i <= n; ++i) {
	if (num % i == 0)
	    return false;
    }
    return true;
}

void bt(int *a, int k) {
    if (k == N) {
	printf("%d", a[0]);
	for (int i = 1; i < N; ++i) {
	    printf(" %d", a[i]);
	}
	printf("\n");
	//printf("%d", a[0]);
	//for (int i = N - 1; i >= 1; --i) {
	//    printf(" %d", a[i]);
	//}
	//printf("\n");
	return;
    }
    for (int i = 1; i <= N; ++i) {
	if (his[i]) continue;
	if (!is_prime(a[k - 1] + i)) continue;
	if (k == N - 1 && !is_prime(a[0] + i)) continue;

	a[k] = i;
	his[i] += 1;
	bt(a, k + 1);
	his[i] -= 1;
	a[k] = 0;
    }
}

void helper() {
    memset(ring, 0, sizeof(ring));
    memset(his, 0, sizeof(his));
    ring[0] = 1;
    his[ring[0]] += 1;
    bt(ring, 1);
}

int main() {
    int tc = 0;

    scanf("%d", &N);
    do {
	tc += 1;
	printf("Case %d:\n", tc);
	helper();
    } while (scanf("%d", &N) != EOF && putchar('\n'));

    return 0;
}
