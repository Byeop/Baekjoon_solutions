#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> g[100];
priority_queue<pair<int, int>> pq;
int dist[100];

int main(void) {
    /* make graph */

    int s = 0;
    fill(dist, dist + 100, 1e9);
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int u = top.second, cost = -top.first;

        if (dist[u] < cost) continue;

        for (auto e : g[u]) {
            int v = e.first, w = e.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({-dist[v], v});
            }
        }
    }

    return 0;
}