#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> g[500010];
int v[500010];

int main(void) {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 2; i <= n; ++i) {
        int p;
        scanf("%d", &p);
        g[p].push_back(i);
    }
    while (q--) {
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; ++i) scanf("%d", v + i);
        ll ans = 0;
        }

    return 0;
}