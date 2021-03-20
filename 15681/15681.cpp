#include <bits/stdc++.h>

using namespace std;

vector<int> g[100010];
int dp[100010], visited[100010];

int dfs(int u) {
    if (visited[u]) return 0;
    visited[u] = 1;
    int &ret = dp[u] = 1;
    for (int v : g[u]) ret += dfs(v);
    return ret;
}

int main(void) {
    int n, r, q;
    scanf("%d %d %d", &n, &r, &q);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(r);
    while (q--) {
        int u;
        scanf("%d", &u);
        printf("%d\n", dp[u]);
    }

    return 0;
}