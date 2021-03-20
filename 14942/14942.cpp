#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int ant[100010];
const int MAX = 17;
int parent[100010][MAX], depth[100010], dist[100010][MAX];

vector<pii> g[100010];

void dfs(int u) {
    for (auto p : g[u]) {
        int v = p.first, w = p.second;
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dist[v][0] = w;
            dfs(v);
        }
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", ant + i);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back(pii(v, w));
        g[v].push_back(pii(u, w));
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
                dist[i][k + 1] = dist[i][k] + dist[parent[i][k]][k];
            }
        }
    }

    printf("1\n");
    for (int i = 2; i <= n; ++i) {
        int u = i;
        for (int k = MAX - 1; k >= 0; --k)
            if (parent[u][k] != -1 && dist[u][k] <= ant[i]) {
                ant[i] -= dist[u][k];
                u = parent[u][k];
            }
        printf("%d\n", u);
    }

    return 0;
}