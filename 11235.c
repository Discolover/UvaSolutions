#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

void build(int p, int L, int R);
int rmq(int p, int L, int R, int i, int j);
void qry(int q, int n);

#define HT 100000

int arr[HT];
int val[HT];
int lastIndex[2 * HT + 1];
/*log2(HT) == 16.609..*/
int st[2 * (1 << 17)];

int main()
{
	int n, q;
	int i, j, cnt, nxt;

	while (scanf("%d %d", &n, &q) == 2) {
		cnt = 1;
		scanf("%d", &nxt);
		for (i = 0; i < n; ++i) {
			arr[i] = nxt;
			val[i] = cnt++;

			if (i < n-1) scanf("%d", &nxt);
			if ((i >= n-1) || arr[i] != nxt) {
				lastIndex[arr[i] + HT] = i;
				cnt = 1;
			} 
		}




		build(0, 0, n - 1);
		qry(q, n);
	}

	return 0;
}

void qry(int q, int n)
{
	int i, j, li, tmp, ans;

	while (q--) {
		scanf("%d %d", &i, &j);
		i -= 1; j -= 1;
		if (val[i] != 1) {
			li = lastIndex[arr[i]+HT];
			if ((j - i + 1) <= (li - i + 1)) {
				ans = j - i + 1;
			} else {
				tmp = rmq(0, 0, n-1, li+1, j);
				ans = ((li-i+1) > tmp) ? (li-i+1) : tmp;
			}
		} else {
			ans = rmq(0, 0, n-1, i, j); 
		}
		printf("%d\n", ans);
	}
}

void build(int p, int L, int R)
{
	if (L == R) {
		st[p] = val[L];
	} else {
		int v1, v2;
		build(2*p + 1, L, (L + R) / 2);
		build(2*p + 2, (L + R) / 2 + 1, R);
		v1 = st[2*p + 1];
		v2 = st[2*p + 2];
		st[p] = (v1 > v2) ? v1 : v2;
	}
}

int rmq(int p, int L, int R, int i, int j)
{
	if (i > R || j < L) return -1;
	if (i <= L && j >= R) return st[p];

	int v1, v2;
	v1 = rmq(2*p+1, L, (L+R)/2, i, j);
	v2 = rmq(2*p+2, (L+R)/2+1, R, i, j);

	if (v1 == -1) return v2;
	if (v2 == -1) return v1;

	return (v1 > v2) ? v1 : v2;
}
