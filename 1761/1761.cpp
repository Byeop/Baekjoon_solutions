#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

const int MAX = 16;
vector<pll> g[40010];
ll parent[40010][MAX], depth[40010];
ll dist[40010], visited[40010];

void dfs(int u) {
    for (auto e : g[u]) {
        int v = e.first;
        if (depth[v] == -1) {
            parent[v][0] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
        }
    }
}

void inorder(int u) {
    visited[u] = true;
    for (auto e : g[u]) {
        int v = e.first, w = e.second;
        if (visited[v]) continue;
        dist[v] = dist[u] + w;
        inorder(v);
    }
}

ll solve(int u, int v) {
    ll d = dist[u] + dist[v];
    if (depth[u] < depth[v]) swap(u, v);
    ll diff = depth[u] - depth[v];
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

    return d - 2 * dist[u];
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(pll(v, w));
        g[v].push_back(pll(u, w));
    }
    memset((void *)parent, -1, sizeof(parent));
    memset((void *)depth, -1, sizeof(depth));
    depth[1] = 0;  // root node;
    dfs(1);
    for (int j = 0; j < MAX - 1; ++j)
        for (int i = 2; i <= n; ++i)
            if (parent[i][j] != -1) parent[i][j + 1] = parent[parent[i][j]][j];

    inorder(1);
    int q;
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%lld\n", solve(u, v));
    }

    return 0;
}