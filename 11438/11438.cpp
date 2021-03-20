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

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;
    dfs(1);
    for (int j = 0; j < MAX - 1; ++j)
        for (int i = 2; i <= n; ++i)
            if (parent[i][j] != -1) parent[i][j + 1] = parent[parent[i][j]][j];

    int q;
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);

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

        printf("%d\n", u);
    }

    return 0;
}