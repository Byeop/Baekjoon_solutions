#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, pair<int, int>> edge;

vector<edge> edges;
int uf[10010], l[10010];

int find(int x) {
    if (uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (l[x] < l[y]) swap(x, y);
    uf[y] = x;
    if (l[x] == l[y]) l[x]++;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, e;
    cin >> n >> e;
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
    }

    for (int i = 1; i <= n; ++i) uf[i] = i;
    sort(edges.begin(), edges.end());
    ll cost = 0;
    for (auto e : edges) {
        int w = e.first, u = e.second.first, v = e.second.second;
        if (find(u) != find(v)) {
            merge(u, v);
            cost += w;
        }
    }
    cout << cost;

    return 0;
}