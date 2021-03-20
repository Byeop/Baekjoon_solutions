#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> edge;

vector<edge> edges;
vector<edge> exclude;
vector<pii> g[50010];

int uf[50010], length[50010];

const int MAX = 16;
int parent[50010][MAX], depth[50010];
pii dist[50010][MAX];

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

void dfs(int u) {
    for (auto p : g[u]) {
        int v = p.first, w = p.second;
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dist[v][0] = pii(w, -1);
            dfs(v);
        }
    }
}

int maxDist(int u, int v, int w) {
    int ret = -1;
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; ++i) {
        if (diff % 2) {
            if (dist[u][i].first != w)
                ret = max(ret, dist[u][i].first);
            else if (dist[u][i].second != -1)
                ret = max(ret, dist[u][i].second);
            u = parent[u][i];
        }
        diff >>= 1;
    }

    if (u != v) {
        for (int i = MAX - 1; i >= 0; --i) {
            if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
                if (dist[u][i].first != w)
                    ret = max(ret, dist[u][i].first);
                else if (dist[u][i].second != -1)
                    ret = max(ret, dist[u][i].second);
                if (dist[v][i].first != w)
                    ret = max(ret, dist[v][i].first);
                else if (dist[v][i].second != -1)
                    ret = max(ret, dist[v][i].second);
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        if (dist[u][0].first != w)
            ret = max(ret, dist[u][0].first);
        else if (dist[u][0].second != -1)
            ret = max(ret, dist[u][0].second);
        if (dist[v][0].first != w)
            ret = max(ret, dist[v][0].first);
        else if (dist[v][0].second != -1)
            ret = max(ret, dist[v][0].second);
        u = parent[u][0];
    }

    return ret;
}

int main(void) {
    // input
    int v, e;
    scanf("%d %d", &v, &e);
    while (e--) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back(edge(w, pii(u, v)));
    }
    // gen mst
    int cost = 0;
    for (int i = 1; i <= v; ++i) uf[i] = i;
    sort(edges.begin(), edges.end());
    for (auto &e : edges) {
        int w = e.first, u = e.second.first, v = e.second.second;
        if (find(u) != find(v)) {
            merge(u, v);
            cost += w;
            g[u].push_back(pii(v, w));
            g[v].push_back(pii(u, w));
        } else
            exclude.push_back(e);
    }
    if (edges.size() - exclude.size() != v - 1) {
        printf("-1");
        return 0;
    }
    // get lca array
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < 50010; ++i)
        for (int j = 0; j < MAX; ++j) dist[i][j] = pii(-1, -1);
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;
    dfs(1);
    for (int j = 0; j < MAX - 1; ++j) {
        for (int i = 1; i <= v; ++i) {
            if (parent[i][j] != -1) {
                parent[i][j + 1] = parent[parent[i][j]][j];
                int a = dist[i][j].first, b = dist[i][j].second;
                int c = dist[parent[i][j]][j].first, d = dist[parent[i][j]][j].second;
                if (a > c)
                    dist[i][j + 1] = pii(a, max(b, c));
                else if (a < c)
                    dist[i][j + 1] = pii(c, max(a, d));
                else
                    dist[i][j + 1] = pii(a, max(b, d));
            }
        }
    }
    // O(ElogV) -- lca를 이용한 u, v 사이의 최단거리 빠르게 구하기
    int ans = 2e9;
    for (auto e : exclude) {
        int w = e.first, u = e.second.first, v = e.second.second;
        int m = maxDist(u, v, w);
        if (m == -1) continue;
        ans = min(ans, cost + w - m);
    }
    printf("%d", ans == 2e9 ? -1 : ans);

    return 0;
}