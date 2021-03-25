#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<ll, ll> pll;
typedef pair<pll, pll> edge;

vector<edge> edges;
bool tree[200010];
int uf[100010], h[100010];

int find(int x) { return (x == uf[x] ? x : uf[x] = find(uf[x])); }

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (h[x] < h[y]) swap(x, y);
    uf[y] = x;
    if (h[x] == h[y]) h[x]++;
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        edges.push_back(edge(pll(w, i), pll(u, v)));
    }

    for (int i = 1; i <= n; ++i) uf[i] = i;

    sort(edges.begin(), edges.end());
    ll mstCost = 0, cnt = 0;
    for (auto e : edges) {
        ll u = e.second.first, v = e.second.second, w = e.first.first, i = e.first.second;
        if (find(u) != find(v)) {
            merge(u, v);
            mstCost += w;
            tree[i] = true;
            cnt++;
        }
    }
    if (cnt != n - 1) {
        printf("-1");
        return 0;
    }

    for (int i = 0; i < m; ++i) {
        if (!tree[i])
            printf("%lld\n", mstCost);
        else {
        }
    }

    return 0;
}