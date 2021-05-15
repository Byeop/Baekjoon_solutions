#include <bits/stdc++.h>

using namespace std;

int p[555], dp[510][510];

int solve(int i, int j) {
    if(i == j) return 0;
    int &ret = dp[i][j];
    if(ret != -1) return ret;
    ret = 1e10;
    for(int k = i;k < j;++k) ret = min(ret, solve(i, k) + solve(k + 1, j) + p[i - 1] * p[k] * p[j]);
    return ret;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i] >> p[i + 1];

    memset(dp, -1, sizeof(dp));
    cout << solve(1, n);

    return 0;
}