#include <bits/stdc++.h>

using namespace std;

vector<int> g[100010];
int parent[100010], visited[100010];

void dfs(int u) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v]) {
            parent[v] = u;
            dfs(v);
        }
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    for (int i = 2; i <= n; ++i) printf("%d\n", parent[i]);

    return 0;
}