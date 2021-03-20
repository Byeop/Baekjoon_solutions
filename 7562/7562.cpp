#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piii;

int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
int visited[310][310];

bool chk(int x, int y, int n) { return x >= 0 && x < n && y >= 0 && y < n && !visited[x][y]; }

int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        queue<piii> q;
        q.push(piii(pii(x, y), 0));
        memset(visited, 0, sizeof(visited));
        visited[x][y] = 1;
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int curx = p.first.first, cury = p.first.second, c = p.second;
            if (curx == a && cury == b) {
                printf("%d\n", c);
                break;
            }
            for (int i = 0; i < 8; ++i) {
                int nx = curx + dx[i], ny = cury + dy[i];
                if (chk(nx, ny, n)) {
                    q.push(piii(pii(nx, ny), c + 1));
                    visited[nx][ny] = 1;
                }
            }
        }
    }

    return 0;
}