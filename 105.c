#include <stdio.h>

#define M 10000

int hmap[M];

int main()
{
    int r, h, l, i, j, minx, maxr = 0;

    scanf("%d %d %d", &l, &h, &r);

    minx = l;
    do {
	for (i = l; i < r; ++i) {
	    if (h > hmap[i]) hmap[i] = h;
	}
	if (r > maxr) maxr = r;
    } while (scanf("%d %d %d", &l, &h, &r) != EOF);

    for (i = minx; ; i = j) {
	printf("%d %d", i, hmap[i]);
	if (i == maxr) break;
	else putchar(' ');
	for (j = i + 1; hmap[j] == hmap[i]; ++j)
	    ;
    }
    putchar('\n');

    return 0;
}
