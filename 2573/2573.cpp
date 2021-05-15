#include <bits/stdc++.h>

using namespace std;

struct p {
    int y, x, di;
};

int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int n, m, g[310][310], v[310][310], t[310][310];
queue<pair<int, int>> q1;
queue<p> q2;

bool chk(int y, int x) {
    if (y >= 0 && y < n && x >= 0 && x < m) return true;
    return false;
}

void dfs(int y, int x) {
    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i], nx = x + dx[i];
        if (chk(ny, nx) && g[ny][nx] && !v[ny][nx]) {
            v[ny][nx] = 1;
            dfs(ny, nx);
        }
    }
}

int cc(void) {
    int ret = 0;
    memset(v, 0, sizeof(v));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (g[i][j] && !v[i][j]) {
                ret += 1;
                dfs(i, j);
            }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
            if (g[i][j] > 0) q1.push({i, j});
        }

    for (int ans = 0;; ++ans) {
        int c = cc();
        if (c > 1) {
            cout << ans;
            return 0;
        }
        if (c == 0) break;

        while (!q1.empty()) {
            auto t = q1.front();
            q1.pop();

            int y = t.first, x = t.second, ib = 0;
            for (int i = 0; i < 4; ++i) {
                int yy = y + dy[i], xx = x + dx[i];
                if (chk(yy, xx) && g[yy][xx] == 0) ib++;
            }
            q2.push({y, x, ib});
        }
        while (!q2.empty()) {
            auto t = q2.front();
            q2.pop();
            int &a = g[t.y][t.x];
            a = max(g[t.y][t.x] - t.di, 0);
            if (a > 0) q1.push({t.y, t.x});
        }
    }
    cout << 0;

    return 0;
}