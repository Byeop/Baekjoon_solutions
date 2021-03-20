#include <bits/stdc++.h>

using namespace std;

int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0, a, b; i < m; ++i) scanf("%d %d", &a, &b);
        printf("%d\n", n - 1);
    }

    return 0;
}