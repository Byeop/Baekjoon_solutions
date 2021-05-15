#include <bits/stdc++.h>

using namespace std;

struct p {
    int s, e, a;
};

int n, dp[30][2];
vector<p> m;

int solve(int i, bool f) {
    if (i == n) return 0;

    int &ret = dp[i][f];
    if (ret != -1) return ret;

    if (f)
        ret = solve(i + 1, false);
    else
        ret = max(solve(i + 1, true) + m[i].a, solve(i + 1, false));
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int s, e, a;
        cin >> s >> e >> a;
        m.push_back({s, e, a});
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(0, false);

    return 0;
}