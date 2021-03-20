#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> edge;

vector<edge> edges;

int uf[200010], length[200010];

const int MAX = 18;
ll parent[200010][MAX], depth[200010], dist[200010][MAX];

vector<pll> g[200010];
map<edge, bool> used;

int find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = find(uf[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (length[x] < length[y]) swap(x, y);
    uf[y] = x;
    if (length[x] == length[y]) length[x]++;
}

void dfs(ll u) {
    for (auto p : g[u]) {
        ll v = p.first, w = p.second;
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dist[v][0] = w;
            dfs(v);
        }
    }
}

int maxDist(int u, int v) {
    ll ret = 0;
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; ++i) {
        if (diff % 2) {
            ret = max(ret, dist[u][i]);
            u = parent[u][i];
        }
        diff >>= 1;
    }
    if (u != v) {
        for (int i = MAX - 1; i >= 0; --i) {
            if (parent[u][i] != 1 && parent[u][i] != parent[v][i]) {
                ret = max(ret, max(dist[u][i], dist[v][i]));
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        ret = max(ret, max(dist[u][0], dist[v][0]));
    }
    return ret;
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        edges.push_back(edge(w, pll(u, v)));
    }

    for (int i = 1; i <= n; ++i) uf[i] = i;
    auto tmp = edges;
    sort(edges.begin(), edges.end());
    ll cost = 0;
    for (int i = 0; i < edges.size(); ++i) {
        auto e = edges[i];
        ll u = e.second.first, v = e.second.second, w = e.first;
        if (find(u) != find(v)) {
            merge(u, v);
            cost += w;
            g[u].push_back(pll(v, w));
            g[v].push_back(pll(u, w));
            used[e] = true;
        }
    }

    memset(dist, -1, sizeof(dist));
    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;
    dfs(1);
    for (int k = 0; k < MAX - 1; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (parent[i][k] != -1) {
                parent[i][k + 1] = parent[parent[i][k]][k];
                dist[i][k + 1] = max(dist[i][k], dist[parent[i][k]][k]);
            }
        }
    }

    for (auto e : tmp) {
        if (used[e])
            printf("%lld\n", cost);
        else {
            ll u = e.second.first, v = e.second.second, w = e.first;
            printf("%lld\n", cost - maxDist(u, v) + w);
        }
    }

    return 0;
}