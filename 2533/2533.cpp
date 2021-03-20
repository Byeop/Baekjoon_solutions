#include <bits/stdc++.h>

using namespace std;

vector<int> in[1000010], g[1000010];
bool visited[1000010];
int dp[1000010][2];

void dfs(int u) {
    visited[u] = true;
    for (int v : in[u]) {
        if (!visited[v]) {
            g[u].push_back(v);
            dfs(v);
        }
    }
}

int solve(int u, bool f) {
    int &ret = dp[u][f];
    if (ret != -1) return ret;

    ret = f;
    for (int v : g[u]) ret += min(solve(v, 1), f ? solve(v, 0) : 2000000);
    return ret;
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        in[u].push_back(v);
        in[v].push_back(u);
    }

    dfs(1);
    memset(dp, -1, sizeof(dp));
    int ans = min(solve(1, 0), solve(1, 1));
    printf("%d", ans);

    return 0;
}