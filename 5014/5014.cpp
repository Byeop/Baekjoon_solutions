#include <bits/stdc++.h>

using namespace std;

queue<pair<int, int>> q;
bool v[1000100];

int main(void) {
    int f, s, g, u, d;
    cin >> f >> s >> g >> u >> d;

    if ((u == 0 && s < g) || (d == 0 && s > g)) {
        cout << "use the stairs";
        return 0;
    }

    q.push({s, 0});
    int n = 1;
    v[s] = 1;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (p.first == g) {
            cout << p.second;
            return 0;
        }
        if (n == f) break;
        int t = p.first - d;
        if (t >= 1 && !v[t]) {
            v[t] = 1;
            n++;
            q.push({t, p.second + 1});
        }
        t = p.first + u;
        if (t <= f && !v[t]) {
            v[t] = 1;
            n++;
            q.push({t, p.second + 1});
        }
    }
    cout << "use the stairs";

    return 0;
}