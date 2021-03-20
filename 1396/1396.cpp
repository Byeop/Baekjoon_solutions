#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> edge;

vector<edge> edges;
vector<ll> g[200010];
ll uf[200010], s[200010], weight[200010];

const int MAX = 18;
int parent[200010][MAX], depth[200010];

void dfs(int u) {
    for (int v : g[u]) {
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dfs(v);
        }
    }
}

ll lca(ll u, ll v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; ++i) {
        if (diff % 2) u = parent[u][i];
        diff >>= 1;
    }
    if (u != v) {
        for (int k = MAX - 1; k >= 0; --k) {
            if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        u = parent[u][0];
    }
    return u;
}

int find(int x) {
    if (uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    uf[y] = x;
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        edges.push_back(edge(w, pll(u, v)));
    }

    for (int i = 1; i <= n + m; ++i) {
        uf[i] = i;
        s[i] = 1;
    }
    sort(edges.begin(), edges.end());
    ll idx = n + 1;
    for (auto e : edges) {
        ll u = e.second.first, v = e.second.second, w = e.first;
        if (find(u) != find(v)) {
            g[idx].push_back(find(u));
            g[idx].push_back(find(v));
            s[idx] = s[find(u)] + s[find(v)];
            weight[idx] = w;
            merge(idx, u);
            merge(idx, v);
            idx++;
        }
    }

    idx--;
    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[idx] = 0;
    for (int i = idx; i > 0; --i) dfs(i);
    for (int k = 0; k < MAX - 1; ++k)
        for (int i = 1; i <= idx; ++i)
            if (parent[i][k] != -1) parent[i][k + 1] = parent[parent[i][k]][k];

    int q;
    scanf("%d", &q);
    while (q--) {
        ll u, v;
        scanf("%lld %lld", &u, &v);
        if (find(u) != find(v)) {
            printf("-1\n");
            continue;
        }
        ll w = lca(u, v);
        printf("%lld %lld\n", weight[w], s[w]);
    }

    return 0;
}