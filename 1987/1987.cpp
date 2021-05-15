#include <bits/stdc++.h>

using namespace std;

char a[30][30];
bool check[30];
int r, c;
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

bool chk(int y, int x) { return y >= 0 && x >= 0 && y < r && x < c; }

int solve(int y, int x) {
    int ret = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (chk(ny, nx) && !check[a[ny][nx] - 'A']) {
            check[a[ny][nx] - 'A'] = 1;
            ret = max(ret, solve(ny, nx) + 1);
            check[a[ny][nx] - 'A'] = 0;
        }
    }
    return ret;
}

int main(void) {
    scanf("%d %d", &r, &c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j) scanf(" %c", &a[i][j]);

    check[a[0][0] - 'A'] = 1;
    cout << solve(0, 0);

    return 0;
}