#include <bits/stdc++.h>

using namespace std;

int uf[1000], comp;
vector<int> f, b;
vector<pair<int, int>> edges;

int find(int x) { return uf[x] == x ? x : uf[x] = find(uf[x]); }
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    comp--;
    uf[x] = y;
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    edges.push_back({0, 0});
    for (int i = 1; i <= n; ++i) uf[i] = i;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (find(u) != find(v)) {
            merge(u, v);
            f.push_back(i);
        }
        edges.push_back({u, v});
    }
    for (int i = 1; i <= n; ++i) uf[i] = i;
    for (int i = m; i > 0; --i) {
        int u = edges[i].first, v = edges[i].second;
        if (find(u) != find(v)) {
            merge(u, v);
            b.push_back(i);
        }
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        for (int i = 1; i <= n; ++i) uf[i] = i;
        comp = n;
        int l, r;
        scanf("%d %d", &l, &r);
        for (int i : f) {
            if (i < l)
                merge(edges[i].first, edges[i].second);
            else
                break;
        }
        for (int i : b) {
            if (i > r)
                merge(edges[i].first, edges[i].second);
            else
                break;
        }
        printf("%d\n", comp);
    }

    return 0;
}