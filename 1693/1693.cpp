#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> g[100010], tree[100010];
bool visited[100010];
const int MAX = 17;
ll dp[100010][MAX + 1];

void dfs(int u) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v]) {
            tree[u].push_back(v);
            dfs(v);
        }
    }
}

ll solve(int u, int color) {
    ll &ret = dp[u][color];
    if (ret != -1) return ret;

    ll t = 0;
    for (int v : tree[u]) {
        ll sub = 1e17;
        for (int i = 1; i <= MAX; ++i) {
            if (i == color) continue;
            sub = min(sub, solve(v, i));
        }
        t += sub;
    }
    return ret = t + color;  // !!!
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(dp, -1, sizeof(dp));
    dfs(1);
    ll ans = 1e17;
    for (int i = 1; i <= MAX; ++i) ans = min(ans, solve(1, i));
    printf("%lld", ans);

    return 0;
}