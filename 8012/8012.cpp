#include <bits/stdc++.h>

using namespace std;

vector<int> g[30010];
int input[5001];
const int MAX = 15;
int parent[30010][MAX], depth[30010];

void dfs(int u) {
    for (int v : g[u]) {
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dfs(v);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; ++i) {
        if (diff % 2) u = parent[u][i];
        diff >>= 1;
    }
    if (u != v) {
        for (int i = MAX - 1; i >= 0; --i) {
            if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        u = parent[u][0];
    }
    return u;
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

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) scanf("%d", input + i);

    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[input[0]] = 1;
    dfs(input[0]);
    for (int k = 0; k < MAX - 1; ++k)
        for (int i = 1; i <= n; ++i)
            if (parent[i][k] != -1) parent[i][k + 1] = parent[parent[i][k]][k];

    int ans = 0;
    for (int i = 1; i < m; ++i) {
        int u = input[i - 1], v = input[i];
        int a = lca(u, v);
        ans += depth[u] - depth[a] + depth[v] - depth[a];
    }
    printf("%d", ans);

    return 0;
}