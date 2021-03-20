#include <bits/stdc++.h>

using namespace std;

int uf[1000010], h[1000010];
int ts[1000010], c;
vector<int> g[1000010], st;
map<string, int> msi;
bool visited[1000010];

int find(int x) {
    if (uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (h[x] > h[y])
        uf[y] = x;
    else
        uf[x] = y;
    if (h[x] == h[y]) h[y]++;
}

bool isMerged(int x, int y) {
    if (x == 0 || y == 0) return false;
    x = find(x);
    y = find(y);
    return x == y;
}

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = true;
    for (int v : g[u]) dfs(v);
    ts[u] = c++;
}

int main(void) {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, Q;
    cin >> n >> m;
    c = 1;
    for (int i = 1; i <= n; ++i) uf[i] = i;
    for (int i = 0; i < m; ++i) {
        string u, v;
        cin >> u >> v;
        if (msi[u] == 0) msi[u] = c++;
        if (msi[v] == 0) msi[v] = c++;
        g[msi[u]].push_back(msi[v]);
        merge(msi[u], msi[v]);
    }

    c = 1;
    for (int i = 1; i <= n; ++i) dfs(i);

    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        string u, v;
        cin >> u >> v;
        int a = msi[u], b = msi[v];
        if (!isMerged(a, b))
            cout << "gg ";
        else {
            if (ts[a] > ts[b])
                cout << u << " ";
            else if (ts[a] < ts[b])
                cout << v << " ";
            else
                cout << "gg ";
        }
    }

    return 0;
}