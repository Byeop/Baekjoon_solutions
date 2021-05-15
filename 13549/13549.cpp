#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int dist[500010];

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    fill(dist, dist + 100010, 1000000000);
    priority_queue<pii> pq;
    pq.push({0, n});
    dist[n] = 0;
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        int u = p.second, time = -p.first;
        if (dist[u] < time) continue;
        if (u < k) {
            if (dist[u] + 1 < dist[u + 1]) {
                dist[u + 1] = dist[u] + 1;
                pq.push({-dist[u + 1], u + 1});
            }
            if (dist[u] < dist[u * 2]) {
                dist[u * 2] = dist[u];
                pq.push({-dist[u * 2], u * 2});
            }
        }
        if (dist[u] + 1 < dist[u - 1]) {
            dist[u - 1] = dist[u] + 1;
            pq.push({-dist[u - 1], u - 1});
        }
    }
    cout << dist[k];

    return 0;
}