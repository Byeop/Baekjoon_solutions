#include <bits/stdc++.h>

using namespace std;

const int MAX = 17;
int parent[100010][MAX], depth[100010];
vector<int> g[100010];

void dfs(int u) {
    for (int v : g[u]) {
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dfs(v);
        }
    }
}

int move(int u, int diff) {
    for (int i = 0; diff; ++i) {
        if (diff % 2) u = parent[u][i];
        diff >>= 1;
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = move(u, depth[u] - depth[v]);
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

int getDist(int u, int v) { return abs(depth[u] + depth[v] - 2 * depth[lca(u, v)]); }

int getMid(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int m = getDist(u, v) / 2;
    return move(u, m);
}

int query(int m, int u, int v, int w) {
    int d1 = getDist(m, u), d2 = getDist(m, v), d3 = getDist(m, w);
    return d1 == d2 && d1 == d3;
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

    memset(depth, -1, sizeof(depth));
    memset(parent, -1, sizeof(parent));
    depth[1] = 1;
    dfs(1);
    for (int k = 0; k < MAX - 1; ++k)
        for (int i = 1; i <= n; ++i)
            if (parent[i][k] != -1) parent[i][k + 1] = parent[parent[i][k]][k];

    int q;
    scanf("%d", &q);
    while (q--) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        int uv = getMid(u, v), uw = getMid(u, w), vw = getMid(v, w);
        if (query(uv, u, v, w))
            printf("%d\n", uv);
        else if (query(uw, u, v, w))
            printf("%d\n", uw);
        else if (query(vw, u, v, w))
            printf("%d\n", vw);
        else
            printf("-1\n");
    }

    return 0;
}