#include <stdio.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

//int p[MAXN], upperBound[MAXN], size[MAXN];
vector<int> p, upperBound, size;

int findSet(int i) {
    return (i == p[i]) ? i : (p[i] = findSet(p[i]));
}

int isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}

void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;

    int x = findSet(i), y = findSet(j);
    if (upperBound[x] > upperBound[y]) {
	p[y] = x;
	size[x] += size[y] + 1;
    } else {
	p[x] = y;
	size[y] += size[x] + 1;
	if (upperBound[y] == upperBound[x])
	    ++upperBound[y];
    }
}

unordered_map<string, int> id;

int main()
{
    int nc, f, nameCnt;
    string s1, s2;

    scanf("%d", &nc);

    while (nc--) {
	scanf("%d", &f);
	nameCnt = 0;
	p.assign(f * 2, 0);
	upperBound.assign(f * 2, 0);
	size.assign(f * 2, 0);
	id.clear();
	for (int i = 0; i < f * 2; ++i)
	    p[i] = i;
	while (f--) {
	    cin >> s1 >> s2;
	    if (id.insert({s1, nameCnt}).second)
		++nameCnt;
	    if (id.insert({s2, nameCnt}).second)
		++nameCnt;
	    unionSet(id[s1], id[s2]);
	    //s1 or s2 doesn't matter
	    printf("%d\n", size[findSet(id[s1])] + 1);
	    //printf("%d\n", id[s1]);
	    //printf("%d\n", id[s2]);
	}
    }

    return 0;
}
