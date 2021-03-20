#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

vector<pll> g[100010];
ll dist[100010];
const int MAX = 17;
ll parent[100010][MAX], depth[100010];

void dfs(ll u) {
    for (auto p : g[u]) {
        ll v = p.first, w = p.second;
        if (dist[v] == -1) {
            dist[v] = dist[u] + w;
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dfs(v);
        }
    }
}

ll move(ll u, ll d) {
    for (int i = 0; d; ++i) {
        if (d % 2) u = parent[u][i];
        d >>= 1;
    }
    return u;
}

ll lca(ll u, ll v) {
    if (depth[u] < depth[v]) swap(u, v);
    ll diff = depth[u] - depth[v];
    u = move(u, diff);
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
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        g[u].push_back(pll(v, w));
        g[v].push_back(pll(u, w));
    }

    memset(dist, -1, sizeof(dist));
    memset(depth, -1, sizeof(depth));
    memset(parent, -1, sizeof(parent));
    dist[1] = depth[1] = 0;
    dfs(1);
    for (int k = 0; k < MAX - 1; ++k)
        for (int i = 1; i <= n; ++i)
            if (parent[i][k] != -1) parent[i][k + 1] = parent[parent[i][k]][k];

    int m;
    scanf("%d", &m);
    while (m--) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            ll u, v;
            scanf("%lld %lld", &u, &v);
            printf("%lld\n", dist[u] + dist[v] - 2 * dist[lca(u, v)]);
        } else {
            ll u, v, k;
            scanf("%lld %lld %lld", &u, &v, &k);
            k--;
            ll a = lca(u, v);
            ll l = depth[u] - depth[a], r = depth[v] - depth[a];
            if (l < k) {
                ll d = r - (k - l);
                printf("%lld\n", move(v, d));
            } else if (l > k)
                printf("%lld\n", move(u, k));
            else
                printf("%lld\n", a);
        }
    }

    return 0;
}