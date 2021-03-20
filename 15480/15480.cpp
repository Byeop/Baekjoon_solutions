#include <bits/stdc++.h>

using namespace std;

vector<int> g[100010];
const int MAX = 20;
int parent[100010][MAX];
int depth[100010];

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
        diff /= 2;
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

    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;
    dfs(1);
    for (int j = 0; j < MAX - 1; ++j)
        for (int i = 1; i <= n; ++i)
            if (parent[i][j] != -1) parent[i][j + 1] = parent[parent[i][j]][j];

    int m;
    scanf("%d", &m);
    while (m--) {
        int r, u, v;
        scanf("%d %d %d", &r, &u, &v);
        int uv = lca(u, v), ur = lca(u, r), vr = lca(v, r);
        int maxDepth = max(depth[uv], max(depth[ur], depth[vr]));
        if (maxDepth == depth[uv])
            printf("%d\n", uv);
        else if (maxDepth == depth[ur])
            printf("%d\n", ur);
        else
            printf("%d\n", vr);
    }

    return 0;
}