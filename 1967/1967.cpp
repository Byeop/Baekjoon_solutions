#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

vector<pii> g[100010];
int dist[100010], visited[100010];

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = true;
    for (auto v : g[u]) {
        if (visited[v.first]) continue;
        dist[v.first] = dist[u] + v.second;
        dfs(v.first);
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        g[u].push_back(pii(v, c));
        g[v].push_back(pii(u, c));
    }

    dfs(1);
    int maxV = max_element(dist, dist + n + 1) - dist;
    memset((void *)dist, 0, sizeof(dist));
    memset((void *)visited, 0, sizeof(visited));
    dfs(maxV);
    printf("%d", *max_element(dist, dist + n + 1));

    return 0;
}