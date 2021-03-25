#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> edge;

vector<edge> edges;
int uf[100010], h[100010];
vector<pll> g[100010];

const int MAX = 17;
int parent[100010][MAX], depth[100010];
ll dist[100010][MAX][2];

int find(int x) { return (x == uf[x] ? x : uf[x] = find(uf[x])); }

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (h[x] < h[y]) swap(x, y);
    uf[y] = x;
    if (h[x] == h[y]) h[x]++;
}

void dfs(int u) {
    for (auto e : g[u]) {
        int v = e.first, w = e.second;
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dist[v][0][w % 2] = w;
            dfs(v);
        }
    }
}

ll maxDist(ll u, ll v, bool f) {
    ll ret = -1;
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; ++i) {
        if (diff & 1) {
            ret = max(ret, dist[u][i][f]);
            u = parent[u][i];
        }
        diff >>= 1;
    }
    if (u != v) {
        for (int k = MAX - 1; k >= 0; --k) {
            if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                ret = max(ret, max(dist[u][k][f], dist[v][k][f]));
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        ret = max(ret, max(dist[u][0][f], dist[v][0][f]));
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
    sort(edges.begin(), edges.end());
    ll mstCost = 0;
    for (auto e : edges) {
        ll u = e.second.first, v = e.second.second, w = e.first;
        if (find(u) != find(v)) {
            merge(u, v);
            mstCost += w;
            g[u].push_back(pll(v, w));
            g[v].push_back(pll(u, w));
        }
    }

    memset(parent, -1, sizeof(parent));
    memset(dist, -1, sizeof(dist));
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;
    dfs(1);
    for (int k = 0; k < MAX - 1; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (parent[i][k] != -1) {
                parent[i][k + 1] = parent[parent[i][k]][k];
                dist[i][k + 1][0] = max(dist[i][k][0], dist[parent[i][k]][k][0]);
                dist[i][k + 1][1] = max(dist[i][k][1], dist[parent[i][k]][k][1]);
            }
        }
    }

    ll ans = 1e18;
    for (auto e : edges) {
        ll u = e.second.first, v = e.second.second, w = e.first;
        ll t = maxDist(u, v, !(w & 1));
        if (t == -1) continue;
        ans = min(ans, mstCost + w - t);
    }
    if (ans == 1e18) ans = -1;
    if (mstCost & 1)
        printf("%lld %lld", mstCost, ans);
    else
        printf("%lld %lld", ans, mstCost);

    return 0;
}