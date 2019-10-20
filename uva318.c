#include <stdio.h>
#include <stdlib.h>

struct vert {
	struct vert *next;
	int n;
	int l;
} **gr;

int *val;

void init(int n)
{
	gr = calloc(n, sizeof *gr);
	val = calloc(n, sizeof *val);
}

void gr_add(int a, int b, int l)
{
	struct vert *vrt;

	vrt = malloc(sizeof *vrt);
	vrt->n = b;
	vrt->l = l;
	vrt->next = gr[a];
	gr[a] = vrt;
}

void free_all()
{
	free(gr);
	free(val);
}

void trav(int v, int sum)
{
	struct vert *it;

	seen[v] = 1;
	val[v] = sum;

	for (it = gr[v]; it != NULL; it = it-next)
    {
        if (!seen[it->n] || 
        val[it->n] > (sum + val[it->n]))
           trav(it->n, sum);
	}
	
}

int main()
{
	int n, m;
	int a, b, l;

	while (scanf("%d%d", &n, &m) && n != 0) {
		while (m--) {
			scanf("%d%d%d", &a, &b, &l);
			gr_add(a, b);
			gr_add(b, a);

		}
	}

	return 0;
}

