#include <stdio.h>
#include <vector>

int coin_val[5] = {1, 5, 10, 25, 50};

int CNT = 0;
std::vector<int> V;

//count(0, type) -> 1
//count(

int DEPTH;

int count(int change, int type) {
    for (int i = 0; i < DEPTH; ++i)
	printf("  ");
    printf("%d, %d\n", change, type);
    if (change == 0) {
	//for (size_t i = 0; i < V.size(); ++i) {
	//    printf("%d ", V[i]);
	//}
	return 1;
    } else if (change < coin_val[type]) {
	return 0;
    }

    DEPTH += 1;
    int c = count(change - coin_val[type], type)
	+ count(change, type + 1);
    DEPTH -= 1;
    return c;
}

int main() {
    int n;

    while (scanf("%d", &n) && n) {
	printf(">%d\n", count(n, 0));
    }

    return 0;
}
