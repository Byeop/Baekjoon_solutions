#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> g[100];
int dist[100];

int main(void) {
    /* make graph */

    int s = 0, n = 100;
    fill(dist, dist + n, 1e9);
    dist[s] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (auto &e : g[u]) {
                int v = e.first, w = e.second;
                if (dist[v] > dist[u] + w) dist[v] = dist[u] + w;
            }
        }
    }

    return 0;
}