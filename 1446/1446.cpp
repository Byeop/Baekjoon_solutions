#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

vector<pii> g[10010];
vector<pii> input;
int dist[10010];

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, D;
    cin >> n >> D;
    for (int i = 0; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        if (v < D) g[v].push_back({D, D - v});
    }

    priority_queue<pii> pq;
    pq.push({0, 0});
    g[0].push_back({D, D});
    for (int i = 0; i <= 10000; ++i) {
        dist[i] = 1000000000;
        g[i].push_back({i + 1, 1});
    }
    dist[0] = 0;
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        int u = t.second, cost = -t.first;

        if (dist[u] < cost) continue;
        for (auto p : g[u]) {
            int v = p.first, w = p.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({-dist[v], v});
            }
        }
    }
    cout << dist[D];

    return 0;
}