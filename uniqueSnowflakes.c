#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

struct Node
{
	int color;

	void *key;
	void *val;
	
	struct Node *p;
	struct Node *l;
	struct Node *r;
};

struct Rbtree
{
	struct Node *head;	
	struct Node *tail;
	int (*cmp)(void *, void *);
};

struct Rbtree *rbtree_init(int (*cmpfunc)(void *, void *))
{
	struct Rbtree *t;	
	
	t = malloc(sizeof *t);	
	t->head = malloc(sizeof *t->head);
	t->tail = malloc(sizeof *t->tail);
	t->cmp = cmpfunc;

	t->head->l = t->head->r = t->tail;
	t->head->color = BLACK;

	t->tail->l = t->tail->r = t->tail;
	t->tail->color = BLACK;

	return t;
}

struct Node *rotate(struct Rbtree *t, struct Node *nd, int left)
{
	struct Node *rpl;

	rpl = (left) ? nd->r : nd->l;

	if (left) {
		nd->r = rpl->l; 
		if (nd->r != t->tail)
			nd->r->p = nd;
		rpl->l = nd;  		
	} else {
		nd->l = rpl->r; 
		if (nd->l != t->tail)
			nd->l->p = nd;
		rpl->r = nd;	
	}
	
	if (nd->p->l == nd) {
		nd->p->l = rpl;
	} else {
		nd->p->r = rpl;
	}

	rpl->p = nd->p;
	nd->p = rpl;		

	return rpl;
}

struct Node *split(struct Rbtree *t, struct Node *c, struct Node *p, struct Node *g)
{
	c->color = RED; c->l->color = BLACK; c->r->color = BLACK;	

	if ( p->color == RED)
	{
		if ( ( p->r == c) != (g->r == p))
			p = rotate(t, p, p->r == c);

		c = rotate(t, g, g->r == p);	
						
		g->color = RED;	

		c->color = BLACK;
	}
	t->head->r->color = BLACK;	
	
	return c;
}

void rbtree_insert(struct Rbtree *t, void *k, void *v)
{
	struct Node *i, *p, *g;

	p = g = t->head;
	i = t->head->r;

	while (i != t->tail)
	{
		if (i->l->color == RED && i->r->color == RED)
			i = p = split(t, i, p, g);

		g = p; p = i;

		if ((*t->cmp)(k, i->key) == 0) {
			free(i->val);
			i->val = v;	
			return;
		}
		else if((*t->cmp)(k, i->key) == -1)
			i = i->l;
		else 
			i = i->r;	
	}
	

	i = malloc(sizeof *i);
	i->key = k;
	i->val = v;
	
	i->p = p;
	i->r = i->l = t->tail;
	
	if (p != t->head && (*t->cmp)(k, p->key) == -1)	
		p->l = i;
	else
		p->r = i;

	split(t, i, p, g);	
}

struct Node *rbtree_find(struct Rbtree *t, void *k)
{
	struct Node *i;

	i = t->head->r;

	while (i != t->tail && (*t->cmp)(k, i->key) != 0) 
	{
		if  ((*t->cmp)(k, i->key) == -1)
			i = i->l;
		else 
			i = i->r;
	}
	
	if (i != t->tail)
		return i;
	
	return NULL;
}

int cmpfunc(void *a, void *b)
{
	if (*(int *)a < *(int *)b)
		return -1;
	else if (*(int *)a == *(int *)b)
		return 0;
	else 
		return 1;
}

void rbtree_clean(struct Rbtree *t)
{
	struct Node *i, *ni;

	i = t->head->r;

	while (i != t->tail)
	{
		if (i->l == t->tail) {
			ni = i->r; 	
			free(i->key);
			if (i->val) free(i->val);
			free(i);
		} else {
			ni = i->l;	
			i->l = ni->r;
			ni->r = i;	
		}	
		i = ni;
	}

	t->head->r = t->tail;
}


int main()
{
	int nOfC, n, i;
	int mark;	
	int max, cnt;
	int *key, *val;
	int id;
	struct Rbtree *tree = rbtree_init(cmpfunc);
	struct Node *nd;

	scanf("%d", &nOfC);
	while (nOfC--)
	{
		cnt = max = 0;
		mark = 0;

		scanf("%d", &n);
		for (i = 1; i <= n; ++i)
		{
			register int v;

			scanf("%d", &id);
			
			if (nd = rbtree_find(tree, (void*)&id))
				v = *(int *)nd->val;
			else 
				v = 0;

			if (v && v > mark) {
				cnt -= v - mark;
				mark = v;	
			}
			
			key = malloc(sizeof *key);
			val = malloc(sizeof *val);
			*key = id; *val = i;

			rbtree_insert(tree, key, val);
			
			++cnt;
			if (cnt > max)
				max = cnt;
		}	
		printf("%d\n", max);
		rbtree_clean(tree);
	}
	return 0;
}
