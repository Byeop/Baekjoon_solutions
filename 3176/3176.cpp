#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

vector<pii> g[100010];
const int MAX = 17;
int p[100010][MAX], d[100010], max_d[100010][MAX], min_d[100010][MAX];

void dfs(int u) {
    for (auto e : g[u]) {
        int v = e.first, w = e.second;
        if (d[v] == -1) {
            d[v] = d[u] + 1;
            p[v][0] = u;
            max_d[v][0] = min_d[v][0] = w;
            dfs(v);
        }
    }
}

pii query(int u, int v) {
    int r0 = 2000000, r1 = 0;
    if (d[u] < d[v]) swap(u, v);
    int diff = d[u] - d[v];
    for (int i = 0; diff; ++i) {
        if (diff % 2) {
            r0 = min(r0, min_d[u][i]);
            r1 = max(r1, max_d[u][i]);
            u = p[u][i];
        }
        diff >>= 1;
    }
    if (u != v) {
        for (int k = MAX - 1; k >= 0; --k) {
            if (p[u][k] != -1 && p[u][k] != p[v][k]) {
                r0 = min(r0, min(min_d[u][k], min_d[v][k]));
                r1 = max(r1, max(max_d[u][k], max_d[v][k]));
                u = p[u][k];
                v = p[v][k];
            }
        }
        r0 = min(r0, min(min_d[u][0], min_d[v][0]));
        r1 = max(r1, max(max_d[u][0], max_d[v][0]));
    }
    return pii(r0, r1);
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(pii(v, w));
        g[v].push_back(pii(u, w));
    }

    memset(d, -1, sizeof(d));
    memset(p, -1, sizeof(p));
    memset(max_d, -1, sizeof(max_d));
    memset(min_d, -1, sizeof(min_d));
    d[1] = 1;
    dfs(1);
    for (int k = 0; k < MAX - 1; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (p[i][k] != -1) {
                p[i][k + 1] = p[p[i][k]][k];
                max_d[i][k + 1] = max(max_d[i][k], max_d[p[i][k]][k]);
                min_d[i][k + 1] = min(min_d[i][k], min_d[p[i][k]][k]);
            }
        }
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        pii p = query(u, v);
        printf("%d %d\n", p.first, p.second);
    }

    return 0;
}