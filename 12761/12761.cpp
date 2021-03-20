#include <bits/stdc++.h>

using namespace std;

int visited[100010];
queue<pair<int, int>> q;

int main(void) {
    int a, b, n, m;
    scanf("%d %d %d %d", &a, &b, &n, &m);
    q.push({n, 0});
    visited[n] = 1;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int c = p.first, t = p.second;
        if (c == m) {
            printf("%d", t);
            return 0;
        }
        if (c + 1 < 100001 && !visited[c + 1]) {
            q.push({c + 1, t + 1});
            visited[c + 1] = 1;
        }
        if (c - 1 >= 0 && !visited[c - 1]) {
            q.push({c - 1, t + 1});
            visited[c - 1] = 1;
        }
        if (c * a < 100001 && !visited[c * a]) {
            q.push({c * a, t + 1});
            visited[c * a] = 1;
        }
        if (c + a < 100001 && !visited[c + a]) {
            q.push({c + a, t + 1});
            visited[c + a] = 1;
        }
        if (c * b < 100001 && !visited[c * b]) {
            q.push({c * b, t + 1});
            visited[c * b] = 1;
        }
        if (c + b < 100001 && !visited[c + b]) {
            q.push({c + b, t + 1});
            visited[c + b] = 1;
        }
        if (c - a >= 0 && !visited[c - a]) {
            q.push({c - a, t + 1});
            visited[c - a] = 1;
        }
        if (c - b >= 0 && !visited[c - b]) {
            q.push({c - b, t + 1});
            visited[c - b] = 1;
        }
    }

    return 0;
}